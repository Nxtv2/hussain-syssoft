/**
 * \author Hussain Muhammad Salama Hanafy Hammad
 */

#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <stdint.h>
#include <time.h>

typedef uint16_t sensor_id_t;
typedef double sensor_value_t;
typedef time_t sensor_ts_t;         // UTC timestamp as returned by time() - notice that the size of time_t is different on 32/64 bit machine
typedef uint16_t room_id_t;
/**
 * structure to hold sensor data
 */
typedef struct {
    sensor_id_t id;         /** < sensor id */
    sensor_value_t value;   /** < sensor value */
    sensor_ts_t ts;         /** < sensor timestamp */
} sensor_data_t;

typedef struct dplist_node dplist_node_t;

struct dplist_node {
    dplist_node_t *prev, *next;
    void *element;
};

typedef struct dplist dplist_t;


struct dplist {
    dplist_node_t *head;

    void *(*element_copy)(void *src_element);

    void (*element_free)(void **element);

    int (*element_compare)(void *x, void *y);
};

typedef struct {
    sensor_id_t sensor_id;        
    room_id_t room_id;         
    double running_average_data[RUN_AVG_LENGTH]; //store sensor values for running average
    int running_average_count;    // number of sensor values
    sensor_ts_t last_modified;
    double running_average;        
} sensor_element_t;


#endif /* _CONFIG_H_ */
