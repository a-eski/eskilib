#include <stdlib.h>
#include "../../eskilib_test.h"

#define ESKILIB_LIST_TYPE size_t
#include "../eskilib_list.h"

void eskilib_list_malloc_default_size_value_test(void)
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0);
	
	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_value_test(void)
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(size);
	
	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

// void eskilib_list_add_null_element_value_test(void)
// {
// 	const size_t size = 16;
// 	eskilib_List* list = NULL;
// 	enum eskilib_List_Result addResult = FAILURE;
// 	
// 	list = eskilib_list_malloc(size);
//
// 	addResult = eskilib_list_add(NULL, list);
// 	
// 	eskilib_assert(addResult == FAILURE_NULL_ELEMENT);
// 	eskilib_assert(list->position == 0);
//
// 	eskilib_list_free(list);
// }

void eskilib_list_add_null_list_value_test(void)
{
	enum eskilib_List_Result addResult = FAILURE;

	addResult = eskilib_list_add(1001, NULL);
	
	eskilib_assert(addResult == FAILURE_NULL_LIST);
}

void eskilib_list_add_one_element_value_test(void)
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	size_t element = 1001;
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(element, list);
	
	eskilib_assert(addResult == SUCCESS);
	eskilib_assert(list->elements[0] == element);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 1);

	eskilib_list_free(list);
}

void eskilib_list_add_until_size_expanded_value_test(void)
{
	const size_t size = 2;
	eskilib_List* list = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	size_t elementThree = 3003;
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(elementOne, list);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementTwo, list);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementThree, list);
	eskilib_assert(addResult == SUCCESS);
	
	eskilib_assert(list->elements[0] == elementOne);
	eskilib_assert(list->elements[1] == elementTwo);
	eskilib_assert(list->elements[2] == elementThree);
	eskilib_assert(list->size == size * 2);
	eskilib_assert(list->position == 3);

	eskilib_list_free(list);
}

void eskilib_list_add_10_value_test(void)
{
	eskilib_List* list = NULL;
	size_t element = 1001;
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		addResult = eskilib_list_add(element, list);
		eskilib_assert(addResult == SUCCESS);
		eskilib_assert(list->elements[i] == element);
		element += 1001;
	}
	
	eskilib_assert(list->position == 10);

	eskilib_list_free(list);
}

void eskilib_list_release_value_tests(void)
{
	// eskilib_test_run("eskilib_list_add_null_element_value_test", eskilib_list_add_null_element_value_test);
	
	eskilib_test_run("eskilib_list_add_null_list_value_test", eskilib_list_add_null_list_value_test);
}

void eskilib_list_value_tests(void)
{
	#ifdef NDEBUG
		eskilib_list_release_value_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_list_malloc_default_size_value_test", eskilib_list_malloc_default_size_value_test);
	
	eskilib_test_run("eskilib_list_malloc_nondefault_size_value_test", eskilib_list_malloc_nondefault_size_value_test);
	
	eskilib_test_run("eskilib_list_add_one_element_value_test", eskilib_list_add_one_element_value_test);

	eskilib_test_run("eskilib_list_add_until_size_expanded_value_test", eskilib_list_add_until_size_expanded_value_test);

	eskilib_test_run("eskilib_list_add_10_value_test", eskilib_list_add_10_value_test);
}

