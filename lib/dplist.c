/**
 * \author Hussain Muhammad Salama Hanafy Hammad
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
char *my_strdup(const char *src);
#include "dplist.h"

/*
 * definition of error codes
 * */
#define DPLIST_NO_ERROR 0
#define DPLIST_MEMORY_ERROR 1 // error due to mem alloc failure
#define DPLIST_INVALID_ERROR 2 //error due to a list operation applied on a NULL list 

#ifdef DEBUG
#define DEBUG_PRINTF(...) 									                                        \
        do {											                                            \
            fprintf(stderr,"\nIn %s - function %s at line %d: ", __FILE__, __func__, __LINE__);	    \
            fprintf(stderr,__VA_ARGS__);								                            \
            fflush(stderr);                                                                         \
                } while(0)
#else
#define DEBUG_PRINTF(...) (void)0
#endif


#define DPLIST_ERR_HANDLER(condition, err_code)                         \
    do {                                                                \
            if ((condition)) DEBUG_PRINTF(#condition " failed\n");      \
            assert(!(condition));                                       \
        } while(0)


/*
 * The real definition of struct list / struct node
 */
typedef struct {
    int id;
    char* name;
} my_element_t;

struct dplist_node {
    dplist_node_t *prev, *next;
    void *element;
};

struct dplist {
    dplist_node_t *head;

    void *(*element_copy)(void *src_element);

    void (*element_free)(void **element);

    int (*element_compare)(void *x, void *y);
};

char *my_strdup(const char *src) {
    size_t length = strlen(src) + 1;
    char *dest = malloc(length);
    if (dest != NULL) {
        memcpy(dest, src, length);
    }
    return dest;
}

dplist_t *dpl_create(// callback functions
        void *(*element_copy)(void *src_element),
        void (*element_free)(void **element),
        int (*element_compare)(void *x, void *y)
) {
    dplist_t *list;
    list = malloc(sizeof(struct dplist));
    DPLIST_ERR_HANDLER(list == NULL, DPLIST_MEMORY_ERROR);
    list->head = NULL;
    list->element_copy = element_copy;
    list->element_free = element_free;
    list->element_compare = element_compare;
    return list;
}


void element_free(void** element) {
    if (element != NULL && *element != NULL) {
        free(*element);
        *element = NULL;
    }
}

int element_compare(void* a, void* b) {
    int* int_a = (int*)a;
    int* int_b = (int*)b;
    if (*int_a < *int_b) {
        return -1;
    } else if (*int_a > *int_b) {
        return 1;
    } else {
        return 0;
    }
}

void* element_copy(void* element) {
    if (element == NULL) {
        return NULL;
    }
    char* original = (char*)element;
    size_t length = strlen(original) + 1;
    char* copy = malloc(length);
    if (copy != NULL) {
        memcpy(copy, original, length);
    }
    return copy;
}
/*
void* element_copy(void* element) {
    if (element == NULL) {
        return NULL;
    }
    char* original = (char*)element;
    size_t length = strlen(original) + 1;
    char* copy = malloc(length);
    if (copy != NULL) {
        memcpy(copy, original, length);
    }
    return copy;
}

void element_free(void ** element) {
    free((((my_element_t*)*element))->name);
    free(*element);
    *element = NULL;
}

int element_compare(void * x, void * y) {
    return ((((my_element_t*)x)->id < ((my_element_t*)y)->id) ? -1 : (((my_element_t*)x)->id == ((my_element_t*)y)->id) ? 0 : 1);
}
*/

void dpl_free(dplist_t **list, bool free_element) {

    //TODO: add your code here
    DPLIST_ERR_HANDLER(list == NULL, DPLIST_INVALID_ERROR);
    if (*list == NULL) return;
    // Free all nodes
    dplist_node_t *current = (*list)->head;
    while (current != NULL) {
        dplist_node_t *temp = current;
        current = current->next;
        if (free_element && (*list)->element_free != NULL) {
            (*list)->element_free(&(temp->element));
        }
        free(temp);
    }
    free(*list);
    *list = NULL;
}

dplist_t *dpl_insert_at_index(dplist_t *list, void *element, int index, bool insert_copy) {

    //TODO: add your code here
    if (list == NULL) return NULL;

    dplist_node_t *list_node = malloc(sizeof(dplist_node_t));
    DPLIST_ERR_HANDLER(list_node == NULL, DPLIST_MEMORY_ERROR);

    if (insert_copy && list->element_copy != NULL) {
        list_node->element = list->element_copy(element);
    } else {
        list_node->element = element;
    }

    if (list->head == NULL) {
        list_node->prev = NULL;
        list_node->next = NULL;
        list->head = list_node;
    } else if (index <= 0) {
        list_node->prev = NULL;
        list_node->next = list->head;
        list->head->prev = list_node;
        list->head = list_node;
    } else {
        dplist_node_t *ref_at_index = dpl_get_reference_at_index(list, index);
        assert(ref_at_index != NULL);
        if (index < dpl_size(list)) {
            list_node->prev = ref_at_index->prev;
            list_node->next = ref_at_index;
            ref_at_index->prev->next = list_node;
            ref_at_index->prev = list_node;
        } else {
            assert(ref_at_index->next == NULL);
            list_node->next = NULL;
            list_node->prev = ref_at_index;
            ref_at_index->next = list_node;
        }
    }
    return list;
}

dplist_t *dpl_remove_at_index(dplist_t *list, int index, bool free_element) {

    //TODO: add your code here
    DPLIST_ERR_HANDLER(list == NULL, DPLIST_INVALID_ERROR);

    if (list->head == NULL) return list;

    dplist_node_t *node_to_remove = dpl_get_reference_at_index(list, index);
    DPLIST_ERR_HANDLER(node_to_remove == NULL, DPLIST_INVALID_ERROR);

    if (node_to_remove == list->head) {
        list->head = node_to_remove->next;
        if (list->head != NULL)
            list->head->prev = NULL;
    } else {
        node_to_remove->prev->next = node_to_remove->next;
        if (node_to_remove->next != NULL)
            node_to_remove->next->prev = node_to_remove->prev;
    }

    if (free_element && list->element_free != NULL) {
        list->element_free(&(node_to_remove->element));
    }

    free(node_to_remove);
    return list;

}

int dpl_size(dplist_t *list) {

    //TODO: add your code here
    if (list == NULL) return -1;

    int count = 0;
    dplist_node_t *current_node = list->head;
    while (current_node != NULL) {
        count++;
        current_node = current_node->next;
    }
    return count;
}

void *dpl_get_element_at_index(dplist_t *list, int index) {

    //TODO: add your code here
    DPLIST_ERR_HANDLER(list == NULL, DPLIST_INVALID_ERROR);

    if (list->head == NULL) return NULL;

    dplist_node_t *node = dpl_get_reference_at_index(list, index);
    if (node == NULL) {
        dplist_node_t *last_node = dpl_get_reference_at_index(list, dpl_size(list) - 1);
        return last_node->element;
    } else {
        return node->element;
    }
}

int dpl_get_index_of_element(dplist_t *list, void *element) {

    //TODO: add your code here
    DPLIST_ERR_HANDLER(list == NULL, DPLIST_INVALID_ERROR);

    int index = 0;
    dplist_node_t *node = list->head;

    while (node != NULL) {
        if (list->element_compare != NULL && list->element_compare(node->element, element) == 0) {
            return index;
        }
        node = node->next;
        index++;
    }
    return -1;
}

dplist_node_t *dpl_get_reference_at_index(dplist_t *list, int index) {

    //TODO: add your code here
    if (list == NULL) return NULL;

    if (list->head == NULL) return NULL;

    int count;
    dplist_node_t *dummy;
    for (dummy = list->head, count = 0; dummy->next != NULL; dummy = dummy->next, count++) {
        if (count >= index) return dummy;
    }
    return dummy;
}

void *dpl_get_element_at_reference(dplist_t *list, dplist_node_t *reference) {

    //TODO: add your code here
    
    if (list == NULL) return NULL;

    if (reference == NULL) return NULL;

    dplist_node_t *current_node = list->head;
    while (current_node != NULL) {
        if (current_node == reference) {
            return current_node->element;
        }
        current_node = current_node->next;
    }

    return NULL;
}

dplist_node_t *dpl_get_first_reference(dplist_t *list){
    if(list == NULL || dpl_size(list) == 0 ) return NULL;

    return list -> head;
}

int dpl_get_index_of_reference(dplist_t *list, dplist_node_t *reference){
    if(list == NULL || reference == NULL || dpl_size(list) == 0) return -1;

    dplist_node_t *current_node = list->head;

    int i = 0;
    while (current_node != NULL) {
        if (current_node == reference) {
            return i;
        }
        current_node = current_node->next;
        i++;
    }

    return -1;
}

dplist_node_t *dpl_get_last_reference(dplist_t *list){
    if(list == NULL || dpl_size(list) == 0) return NULL;

    return dpl_get_reference_at_index(list, dpl_size(list) - 1);
}

dplist_node_t *dpl_get_next_reference(dplist_t *list, dplist_node_t *reference){
    if(list == NULL || dpl_size(list) == 0) return NULL;

    if(dpl_get_index_of_reference(list, reference) == -1) return NULL;

    return reference -> next;
}

dplist_node_t *dpl_get_previous_reference(dplist_t *list, dplist_node_t *reference){
    if(list == NULL || dpl_size(list) == 0) return NULL;

    if(dpl_get_index_of_reference(list, reference) == -1) return NULL;

    return reference -> prev;
}

dplist_node_t *dpl_get_reference_of_element(dplist_t *list, void *element){
    if(list == NULL || dpl_size(list) == 0) return NULL;

    if(dpl_get_index_of_element(list, element) == -1) return NULL;

    return dpl_get_reference_at_index(list, dpl_get_index_of_element(list, element));
}



dplist_t *dpl_insert_at_reference(dplist_t *list, void *element, dplist_node_t *reference, bool insert_copy){
    if(list == NULL || reference == NULL) return NULL;

    if(dpl_get_index_of_reference(list, reference) == -1) return list;
    return dpl_insert_at_index(list, element, dpl_get_index_of_reference(list, reference), insert_copy);
}

dplist_t *dpl_insert_sorted(dplist_t *list, void *element, bool insert_copy){
    if(list == NULL) return NULL;
    int size = dpl_size(list);
    for (int i = 0; i < size; i++)
    {
        if(list -> element_compare(dpl_get_element_at_index(list, i), element) == 1){
            return dpl_insert_at_index(list, element, i, insert_copy);
        }
    }
    return dpl_insert_at_index(list, element, size, insert_copy);

}

dplist_t *dpl_remove_at_reference(dplist_t *list, dplist_node_t *reference, bool free_element){
    if(list == NULL || reference == NULL) return NULL;

    if(dpl_get_index_of_reference(list, reference) == -1) return list;

    return dpl_remove_at_index(list, dpl_get_index_of_reference(list, reference), free_element);
}

dplist_t *dpl_remove_element(dplist_t *list, void *element, bool free_element){
    if(list == NULL) return NULL;
    if(dpl_get_index_of_element(list, element) == -1) return list;

    return dpl_remove_at_index(list, dpl_get_index_of_element(list, element), free_element);
}


