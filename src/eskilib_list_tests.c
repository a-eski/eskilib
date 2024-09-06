#include <stdlib.h>
#include "eskilib_list.h"
#include "eskilib_test.h"

void eskilib_list_malloc_no_sizeOfElement_set_test(void)
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0, 0); 
	
	eskilib_assert(list == NULL);
}

void eskilib_list_malloc_default_size_test(void)
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0, sizeof(size_t));
	
	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_test(void)
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(size, sizeof(size_t));
	
	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_add_null_element_test(void)
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size, sizeof(size_t*));

	addResult = eskilib_list_add(NULL, list);
	
	eskilib_assert(addResult == FAILURE_NULL_ELEMENT);
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_add_null_list_test(void)
{
	size_t* element = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;

	addResult = eskilib_list_add(element, NULL);
	
	eskilib_assert(addResult == FAILURE_NULL_LIST);

	free(element);
}

void eskilib_list_add_one_element_test(void)
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	size_t* element = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;
	
	list = eskilib_list_malloc(size, sizeof(element));

	addResult = eskilib_list_add(element, list);
	
	eskilib_assert(addResult == SUCCESS);
	eskilib_assert(*(size_t*)list->elements[0] == *element);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 1);

	free(element);
	eskilib_list_free(list);
}

void eskilib_list_add_until_size_expanded_test(void)
{
	const size_t size = 2;
	eskilib_List* list = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	size_t* elementThree = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	elementOne = malloc(sizeof(elementOne));
	*elementOne = 1001;
	elementTwo = malloc(sizeof(elementOne));
	*elementTwo = 2002;
	elementThree = malloc(sizeof(elementOne));
	*elementThree = 3003;
	
	list = eskilib_list_malloc(size, sizeof(elementOne));

	addResult = eskilib_list_add(elementOne, list);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementTwo, list);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementThree, list);
	eskilib_assert(addResult == SUCCESS);
	
	eskilib_assert(*(size_t*)list->elements[0] == *elementOne);
	eskilib_assert(*(size_t*)list->elements[1] == *elementTwo);
	eskilib_assert(*(size_t*)list->elements[2] == *elementThree);
	eskilib_assert(list->size == size * 2);
	eskilib_assert(list->position == 3);

	free(elementOne);
	free(elementTwo);
	free(elementThree);
	eskilib_list_free(list);
}

void eskilib_list_release_tests(void)
{
	eskilib_test_run("eskilib_list_malloc_no_sizeOfElement_set_test", eskilib_list_malloc_no_sizeOfElement_set_test);

	eskilib_test_run("eskilib_list_add_null_element_test", eskilib_list_add_null_element_test);
	
	eskilib_test_run("eskilib_list_add_null_list_test", eskilib_list_add_null_list_test);
}

void eskilib_list_tests(void)
{
	#ifdef NDEBUG
		eskilib_list_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_list_malloc_default_size_test", eskilib_list_malloc_default_size_test);
	
	eskilib_test_run("eskilib_list_malloc_nondefault_size_test", eskilib_list_malloc_nondefault_size_test);
	
	eskilib_test_run("eskilib_list_add_one_element_test", eskilib_list_add_one_element_test);

	eskilib_test_run("eskilib_list_add_until_size_expanded_test", eskilib_list_add_until_size_expanded_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_list_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
