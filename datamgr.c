#include <stdio.h>
#include <stdint.h>
#include "datamgr.h"
#include "config.h"
#include "lib/dplist.h"



// Define any necessary data structures and global variables here
static dplist_t *sensorList;

void datamgr_parse_sensor_files(FILE *fp_sensor_map, FILE *fp_sensor_data) {


	ERROR_HANDLER(fp_sensor_map == NULL || fp_sensor_data == NULL, "Couldn't open files");
	sensorList = dpl_create(element_copy, element_free, element_compare);

	//populate sensorList
	char buf[20];
    sensor_element_t sensor;
    while (fgets(buf, sizeof(buf), fp_sensor_map) != NULL) {
        sscanf(buf, "%hu%hu", &(sensor.room_id), &(sensor.sensor_id));
        // Initialize other fields of 'sensor' as needed
        dpl_insert_at_index(sensorList, &sensor, dpl_size(sensorList), true);
        printf("New sensor Room id %hu Sensor id %hu\n", sensor.room_id, sensor.sensor_id);
      
    }

    // read and process sensor data file
    sensor_data_t sd;
    while (fread(&sd, sizeof(sensor_data_t), 1, fp_sensor_data) != 0) {
        // find the coresponding sensor_element_t in the list based on id
        sensor_element_t *sensor_elem = NULL; // Use dpl_get_element_at_index or similar
         for (int i = 0; i < dpl_size(sensorList); i++) {
            sensor_element_t *current_sensor = dpl_get_element_at_index(sensorList, i);
            if (current_sensor->sensor_id == sd.id) {
                sensor_elem = current_sensor;
                break;
            }
        }
        
        // update the sensor_element_t fields based on sensor data
        if (sensor_elem != NULL) {
            sensor_elem->last_modified = sd.ts;
			double sum = 0.0;
            for (int i = 0; i < RUN_AVG_LENGTH; i++) {
                sum += sensor_elem->running_average_data[i];
            }
            if (sensor_elem->running_average_count < RUN_AVG_LENGTH) {
                sensor_elem->running_average_data[sensor_elem->running_average_count] = sd.value;
                sensor_elem->running_average_count++;
            } else {
                for (int i = 0; i < RUN_AVG_LENGTH - 1; i++) {
                    sensor_elem->running_average_data[i] = sensor_elem->running_average_data[i + 1];
                }
                sensor_elem->running_average_data[RUN_AVG_LENGTH - 1] = sd.value;
            }

            // Calculate and store the new running average
            double new_average = (sum + sd.value) / (sensor_elem->running_average_count);
            sensor_elem->running_average = new_average;

            //check temp
            if (sd.value < SET_MIN_TEMP) {
                fprintf(stderr, "Sensor %hu Room %hu is below the limit of %g *C , currently at %g *C at %ld\n",
                        sd.id, sensor_elem->room_id, (double) SET_MIN_TEMP, sd.value, sd.ts);
            } else if (sd.value > SET_MAX_TEMP) {
                fprintf(stderr, "Sensor %hu Room %hu is above the limit of %g *C , currently at %g *C at %ld\n",
                        sd.id, sensor_elem->room_id, (double) SET_MAX_TEMP, sd.value, sd.ts);
            }
        }
    }
    
    // Clean up resources
    dpl_free(&sensorList, false); 

    // Close file pointers
    fclose(fp_sensor_map);
    fclose(fp_sensor_data);

}

void datamgr_free() {
    if (sensorList != NULL) {
        dpl_free(&sensorList, true);
    }

}

uint16_t datamgr_get_room_id(sensor_id_t sensor_id) {
    ERROR_HANDLER(sensorList == NULL, "sensorList is not initialized");

    for (int i = 0; i < dpl_size(sensorList); i++) {
        sensor_element_t *current_sensor = dpl_get_element_at_index(sensorList, i);
        if (current_sensor->sensor_id == sensor_id) {
            // Return the room ID of the found sensor_element_t
            return current_sensor->room_id;
        }
    }
    ERROR_HANDLER(1, "Invalid sensor ID");
    return -1; // This line will never be reached due to the ERROR_HANDLER
}

sensor_value_t datamgr_get_avg(sensor_id_t sensor_id) {

    ERROR_HANDLER(sensorList == NULL, "sensorList is not initialized");

    // Find the corresponding sensor_element_t in the list based on sensor_id
    sensor_element_t *sensor_elem = NULL;
    for (int i = 0; i < dpl_size(sensorList); i++) {
        sensor_element_t *current_sensor = dpl_get_element_at_index(sensorList, i);
        if (current_sensor->sensor_id == sensor_id) {
            sensor_elem = current_sensor;
            break;
        }
    }

    // Use ERROR_HANDLER for handling invalid sensor IDs
    ERROR_HANDLER(sensor_elem == NULL, "Invalid sensor ID");

    // Calculate and return the running average of the given sensor
    double sum = 0.0;
    for (int i = 0; i < RUN_AVG_LENGTH; i++) {
        sum += sensor_elem->running_average_data[i];
    }
    return sum / sensor_elem->running_average_count;
}

time_t datamgr_get_last_modified(sensor_id_t sensor_id) {
    ERROR_HANDLER(sensorList == NULL, "sensorList is not initialized");

    for (int i = 0; i < dpl_size(sensorList); i++) {
        sensor_element_t *current_sensor = dpl_get_element_at_index(sensorList, i);
        if (current_sensor->sensor_id == sensor_id) {
            return current_sensor->last_modified;
        }
    }
    ERROR_HANDLER(1, "Invalid sensor ID");
}

int datamgr_get_total_sensors() {  
    if (sensorList != NULL) {
		return dpl_size(sensorList);   
	}
	return 0;
}
