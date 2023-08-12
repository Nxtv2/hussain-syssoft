/**
 * \author Ahmed Mohamed Ahmed Ibrahim Eshra
 */

#define _GNU_SOURCE

#include "config.h"
#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <inttypes.h>
#include <pthread.h>
#include <string.h>
#include "lib/dplist.h"
#include "lib/errmacros.h"
#include <assert.h>
//#include "sbuffer.h"


typedef struct {
	int id;
	//char* name;
} my_element_t;

void* element_copy(void * element);
void element_free(void ** element);
int element_compare(void * x, void * y);

void * element_copy(void * element) {
	my_element_t* copy = malloc(sizeof (my_element_t));
	assert(copy != NULL);
	//char* new_name;
	//asprintf(&new_name,"%s",((my_element_t*)element)->name);
	copy->id = ((my_element_t*)element)->id;
	//copy->name = new_name;
	return (void *) copy;
}

void element_free(void ** element) {
	//free((((my_element_t*)*element))->name);
	free(*element);
	*element = NULL;
}

int element_compare(void * x, void * y) {
	return ((((my_element_t*)x)->id < ((my_element_t*)y)->id) ? -1 : (((my_element_t*)x)->id == ((my_element_t*)y)->id) ? 0 : 1);
}

void setup(void) {
	// Implement pre-test setup
}

void teardown(void) {
	// Implement post-test teardown
}

START_TEST(test_dpl_free_nulllist_nocallback)
	{
		// Test free NULL, don't use callback
		dplist_t *list = NULL;
		dpl_free(&list, false);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_nulllist_yescallback)
	{
		// Test free NULL, use callback
		dplist_t *list = NULL;
		dpl_free(&list, true);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_emptylist_nocallback)
	{
		// Test free empty list, don't use callback
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		dpl_free(&list, false);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_emptylist_yescallback)
	{
		// Test free empty list, use callback
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		dpl_free(&list, true);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_oneitemlist_nocallback)
	{
		// Test free one element list, don't use callback
		dplist_t *list = dpl_create(&element_copy, &element_free, &element_compare);
		my_element_t elem;
		dpl_insert_at_index(list, &elem, 0, false);
		dpl_free(&list, false);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_oneitemlist_yescallback)
	{
		// Test free one element list, use callback
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem;
		dpl_insert_at_index(list, &elem, 0, true);
		dpl_free(&list, true);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_manyitemlist_nocallback)
	{
		// Test free many elements list, don't use callback
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem1, elem2, elem3;
		dpl_insert_at_index(list, &elem1, 0, false);
		dpl_insert_at_index(list, &elem2, 0, false);
		dpl_insert_at_index(list, &elem3, 0, false);
		dpl_free(&list, false);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_free_manyitemlist_yescallback)
	{
		// Test free many elements list, use callback
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem1, elem2, elem3;
		dpl_insert_at_index(list, &elem1, 0, true);
		dpl_insert_at_index(list, &elem2, 0, true);
		dpl_insert_at_index(list, &elem3, 0, true);
		dpl_free(&list, true);
		ck_assert_int_eq(NULL, list);
	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_nulllist_nullreference)
	{
		ck_assert(NULL == dpl_get_element_at_reference(NULL, NULL));
	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_emptylist_nullreference)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert(NULL == dpl_get_element_at_reference(list, NULL));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_oneitemlist_nullreference)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem;
		dpl_insert_at_index(list, &elem, 0, false);
		ck_assert(NULL == dpl_get_element_at_reference(list, NULL));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_manyitemlist_nullreference)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3;
		dpl_insert_at_index(list, &elem, 0, false);
		dpl_insert_at_index(list, &elem2, 0, false);
		dpl_insert_at_index(list, &elem3, 0, false);
		ck_assert(NULL == dpl_get_element_at_reference(list, NULL));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_nulllist_referencenotinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_emptylist_referencenotinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_oneitemlist_referencenotinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_manyitemlist_referencenotinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_nulllist_referenceinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_emptylist_referenceinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_oneitemlist_referenceinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_manyitemlist_referenceinlist)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_nulllist_firstelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_emptylist_firstelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_oneitemlist_firstelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_manyitemlist_firstelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_nulllist_lastelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_emptylist_lastelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_oneitemlist_lastelement)
	{

	}
END_TEST

START_TEST(test_dpl_get_element_at_reference_manyitemlist_lastelement)
	{

	}
END_TEST

START_TEST(test_dpl_insert_at_index_nulllist_negativeoneindex)
	{
		my_element_t elem;
		ck_assert_int_eq(NULL, dpl_insert_at_index(NULL, &elem, -1, false));
	}
END_TEST

START_TEST(test_dpl_insert_at_index_emptylist_negativeoneindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_oneitemlist_negativeoneindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2; 
		elem.id = 101;
		elem2.id = 102;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		ck_assert_int_eq(2, dpl_size(list));
		ck_assert_int_eq(102, *(int *)(list -> head -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_manyitemlist_negativeoneindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(103, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_nulllist_zeroindex)
	{
		my_element_t elem;
		ck_assert_int_eq(NULL, dpl_insert_at_index(NULL, &elem, 0, false));
	}
END_TEST

START_TEST(test_dpl_insert_at_index_emptylist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, 0, false);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_oneitemlist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2; 
		elem.id = 101;
		elem2.id = 102;
		dpl_insert_at_index(list, &elem, 0, false);
		dpl_insert_at_index(list, &elem2, 0, false);
		ck_assert_int_eq(2, dpl_size(list));
		ck_assert_int_eq(102, *(int *)(list -> head -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_manyitemlist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, 0, false);
		dpl_insert_at_index(list, &elem2, 0, false);
		dpl_insert_at_index(list, &elem3, 0, false);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(103, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_nulllist_99index)
	{
		my_element_t elem; 
		ck_assert_int_eq(NULL, dpl_insert_at_index(NULL, &elem, 99, false));
	}
END_TEST

START_TEST(test_dpl_insert_at_index_emptylist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, 99, false);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_oneitemlist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2; 
		elem.id = 101;
		elem2.id = 102;
		dpl_insert_at_index(list, &elem, 99, false);
		dpl_insert_at_index(list, &elem2, 99, false);
		ck_assert_int_eq(2, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_manyitemlist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, 99, false);
		dpl_insert_at_index(list, &elem2, 99, false);
		dpl_insert_at_index(list, &elem3, 99, false);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(103, *(int *)(list -> head -> next -> next -> element));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_nulllist_copytrue)
	{
		my_element_t elem; 
		ck_assert_int_eq(NULL, dpl_insert_at_index(NULL, &elem, -1, true));
	}
END_TEST

START_TEST(test_dpl_insert_at_index_emptylist_copytrue)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, true);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		dpl_free(&list, true);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_oneitemlist_copytrue)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2; 
		elem.id = 101;
		elem2.id = 102;
		dpl_insert_at_index(list, &elem, -1, true);
		dpl_insert_at_index(list, &elem2, -1, true);
		ck_assert_int_eq(2, dpl_size(list));
		ck_assert_int_eq(102, *(int *)(list -> head -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> element));
		dpl_free(&list, true);
	}
END_TEST

START_TEST(test_dpl_insert_at_index_manyitemlist_copytrue)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, true);
		dpl_insert_at_index(list, &elem2, -1, true);
		dpl_insert_at_index(list, &elem3, -1, true);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(103, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> next -> element));
		dpl_free(&list, true);
	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_nulllist_elementnotnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_emptylist_elementnotnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_oneitemlist_elementnotnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_manyitemlist_elementnotnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_nulllist_elementnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_emptylist_elementnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_oneitemlist_elementnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_reference_of_element_manyitemlist_elementnull)
	{

	}
END_TEST

START_TEST(test_dpl_get_first_reference_nulllist)
	{
		ck_assert_int_eq(NULL, dpl_get_first_reference(NULL));
	}
END_TEST

START_TEST(test_dpl_get_first_reference_emptylist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(NULL, dpl_get_first_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_first_reference_oneitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		ck_assert_int_eq(list -> head, dpl_get_first_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_first_reference_manyitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(103, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> next -> element));
		ck_assert_int_eq(list -> head, dpl_get_first_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_last_reference_nulllist)
	{
		ck_assert_int_eq(NULL, dpl_get_last_reference(NULL));
	}
END_TEST

START_TEST(test_dpl_get_last_reference_emptylist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(NULL, dpl_get_last_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_last_reference_oneitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(1, dpl_size(list));
		ck_assert_int_eq(101, *(int *)(list -> head -> element));
		ck_assert_int_eq(list -> head, dpl_get_last_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_last_reference_manyitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(3, dpl_size(list));
		ck_assert_int_eq(103, *(int *)(list -> head -> element));
		ck_assert_int_eq(102, *(int *)(list -> head -> next -> element));
		ck_assert_int_eq(101, *(int *)(list -> head -> next -> next -> element));
		ck_assert_int_eq(list -> head -> next -> next, dpl_get_last_reference(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_size_nulllist)
	{
		ck_assert_int_eq(-1, dpl_size(NULL));
	}
END_TEST

START_TEST(test_dpl_size_emptylist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(0, dpl_size(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_size_oneitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(1, dpl_size(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_size_manyitemlist)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(3, dpl_size(list));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_nulllist_negativeone)
	{
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(NULL, -1));
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_emptylist_negativeone)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(list, -1));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_oneitemlist_negativeone)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(list -> head, dpl_get_reference_at_index(list, -1));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_manyitemlist_negativeone)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(list -> head, dpl_get_reference_at_index(list, -1));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_nulllist_zeroindex)
	{
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(NULL, 0));
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_emptylist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(list, 0));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_oneitemlist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(list -> head, dpl_get_reference_at_index(list, 0));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_manyitemlist_zeroindex)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(list -> head, dpl_get_reference_at_index(list, 0));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_nulllist_99index)
	{
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(NULL, 99));
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_emptylist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		ck_assert_int_eq(NULL, dpl_get_reference_at_index(list, 99));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_oneitemlist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem; 
		elem.id = 101;
		dpl_insert_at_index(list, &elem, -1, false);
		ck_assert_int_eq(list -> head, dpl_get_reference_at_index(list, 99));
		dpl_free(&list, false);
	}
END_TEST

START_TEST(test_dpl_get_reference_at_index_manyitemlist_99index)
	{
		dplist_t *list = dpl_create(element_copy, element_free, element_compare);
		my_element_t elem, elem2, elem3; 
		elem.id = 101;
		elem2.id = 102;
		elem3.id = 103;
		dpl_insert_at_index(list, &elem, -1, false);
		dpl_insert_at_index(list, &elem2, -1, false);
		dpl_insert_at_index(list, &elem3, -1, false);
		ck_assert_int_eq(list -> head -> next -> next, dpl_get_reference_at_index(list, 99));
		dpl_free(&list, false);
	}
END_TEST

int main(void) {
	Suite *s1 = suite_create("DPLIST Test");
	TCase *main_test_case = tcase_create("");
	suite_add_tcase(s1, main_test_case);
	//tcase_add_checked_fixture(main_test_case, setup, teardown);

	tcase_add_test(main_test_case, test_dpl_free_nulllist_nocallback);
	tcase_add_test(main_test_case, test_dpl_free_emptylist_nocallback);
	tcase_add_test(main_test_case, test_dpl_free_oneitemlist_nocallback);
	tcase_add_test(main_test_case, test_dpl_free_manyitemlist_nocallback);

	tcase_add_test(main_test_case, test_dpl_free_nulllist_yescallback);
	tcase_add_test(main_test_case, test_dpl_free_emptylist_yescallback);
	tcase_add_test(main_test_case, test_dpl_free_oneitemlist_yescallback);
	tcase_add_test(main_test_case, test_dpl_free_manyitemlist_yescallback);

	tcase_add_test(main_test_case, test_dpl_get_element_at_reference_nulllist_nullreference);
	tcase_add_test(main_test_case, test_dpl_get_element_at_reference_emptylist_nullreference);
	tcase_add_test(main_test_case, test_dpl_get_element_at_reference_oneitemlist_nullreference);
	tcase_add_test(main_test_case, test_dpl_get_element_at_reference_manyitemlist_nullreference);
	
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_nulllist_referencenotinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_emptylist_referencenotinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_oneitemlist_referencenotinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_manyitemlist_referencenotinlist);
	
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_nulllist_referenceinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_emptylist_referenceinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_oneitemlist_referenceinlist);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_manyitemlist_referenceinlist);
	
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_nulllist_firstelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_emptylist_firstelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_oneitemlist_firstelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_manyitemlist_firstelement);
	
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_nulllist_lastelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_emptylist_lastelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_oneitemlist_lastelement);
	// tcase_add_test(main_test_case, test_dpl_get_element_at_reference_manyitemlist_lastelement);
	
	tcase_add_test(main_test_case, test_dpl_insert_at_index_nulllist_negativeoneindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_emptylist_negativeoneindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_oneitemlist_negativeoneindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_manyitemlist_negativeoneindex);
	
	tcase_add_test(main_test_case, test_dpl_insert_at_index_nulllist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_emptylist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_oneitemlist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_manyitemlist_zeroindex);
	
	tcase_add_test(main_test_case, test_dpl_insert_at_index_nulllist_99index);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_emptylist_99index);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_oneitemlist_99index);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_manyitemlist_99index);
	
	tcase_add_test(main_test_case, test_dpl_insert_at_index_nulllist_copytrue);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_emptylist_copytrue);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_oneitemlist_copytrue);
	tcase_add_test(main_test_case, test_dpl_insert_at_index_manyitemlist_copytrue);
	
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_nulllist_elementnotnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_emptylist_elementnotnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_oneitemlist_elementnotnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_manyitemlist_elementnotnull);
	
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_nulllist_elementnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_emptylist_elementnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_oneitemlist_elementnull);
	// tcase_add_test(main_test_case, test_dpl_get_reference_of_element_manyitemlist_elementnull);
	
	tcase_add_test(main_test_case, test_dpl_get_first_reference_nulllist);
	tcase_add_test(main_test_case, test_dpl_get_first_reference_emptylist);
	tcase_add_test(main_test_case, test_dpl_get_first_reference_oneitemlist);
	tcase_add_test(main_test_case, test_dpl_get_first_reference_manyitemlist);
	
	tcase_add_test(main_test_case, test_dpl_get_last_reference_nulllist);
	tcase_add_test(main_test_case, test_dpl_get_last_reference_emptylist);
	tcase_add_test(main_test_case, test_dpl_get_last_reference_oneitemlist);
	tcase_add_test(main_test_case, test_dpl_get_last_reference_manyitemlist);
	
	tcase_add_test(main_test_case, test_dpl_size_nulllist);
	tcase_add_test(main_test_case, test_dpl_size_emptylist);
	tcase_add_test(main_test_case, test_dpl_size_oneitemlist);
	tcase_add_test(main_test_case, test_dpl_size_manyitemlist);
	
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_nulllist_negativeone);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_emptylist_negativeone);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_oneitemlist_negativeone);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_manyitemlist_negativeone);
	
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_nulllist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_emptylist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_oneitemlist_zeroindex);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_manyitemlist_zeroindex);
	
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_nulllist_99index);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_emptylist_99index);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_oneitemlist_99index);
	tcase_add_test(main_test_case, test_dpl_get_reference_at_index_manyitemlist_99index);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	
	// tcase_add_test(main_test_case, test_dpl_free_nulllist_);
	// tcase_add_test(main_test_case, test_dpl_free_emptylist_);
	// tcase_add_test(main_test_case, test_dpl_free_oneitemlist_);
	// tcase_add_test(main_test_case, test_dpl_free_manyitemlist_);
	

	SRunner *sr = srunner_create(s1);
	srunner_run_all(sr, CK_NORMAL);
	srunner_free(sr);
	return 0;
}
