/**
 * \author Hussain Muhammad Salama Hanafy Hammad
 */

#include <stdio.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dplist.h"

typedef struct {
    int id;
    char* name;
} my_element_t;

void* element_copy(void * element);
void element_free(void ** element);
int element_compare(void * x, void * y);


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
void * element_copy(void * element) {
    my_element_t* copy = malloc(sizeof (my_element_t));
    char* new_name;
    asprintf(&new_name,"%s",((my_element_t*)element)->name);
    assert(copy != NULL);
    copy->id = ((my_element_t*)element)->id;
    copy->name = new_name;
    return (void *) copy;
}
*/
void element_free(void ** element) {
    free((((my_element_t*)*element))->name);
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
START_TEST(test_ListFree)
    {
        // Test free NULL, don't use callback
        dplist_t *list = NULL;
        dpl_free(&list, false);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free NULL, use callback
        list = NULL;
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free empty list, don't use callback
        list = dpl_create(element_copy, element_free, element_compare);
        dpl_free(&list, false);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // Test free empty list, use callback
        list = dpl_create(element_copy, element_free, element_compare);
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");

        // TODO : Test free with one element, also test if inserted elements are set to NULL
        list = dpl_create(element_copy, element_free, element_compare);
        char *element = "Hussain";
        list = dpl_insert_at_index(list, element, 0, true);
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");
        //ck_assert_msg(element == NULL, "Failure: expected element to be NULL");

        // TODO : Test free with multiple element, also test if inserted elements are set to NULL
        list = dpl_create(element_copy, element_free, element_compare);
        char *element1 = "Hussain";
        char *element2 = "Hammad";
        list = dpl_insert_at_index(list, element1, 0, true);
        list = dpl_insert_at_index(list, element2, 1, true);
        dpl_free(&list, true);
        ck_assert_msg(list == NULL, "Failure: expected result to be NULL");
        //ck_assert_msg(element1  == NULL, "Failure: expected element to be NULL");
        //ck_assert_msg(element2 == NULL, "Failure: expected element to be NULL");

    }
END_TEST

//START_TEST(test_nameOfYourTest)
//  Add other testcases here...
//END_TEST

int main(void) {
    Suite *s1 = suite_create("LIST_EX3");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_checked_fixture(tc1_1, setup, teardown);
    tcase_add_test(tc1_1, test_ListFree);
    // Add other tests here...

    srunner_run_all(sr, CK_VERBOSE);

    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
