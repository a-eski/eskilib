#include <stdlib.h>
#include "../../eski_test.h"

#define eski_LIST_TYPE size_t
#include "../eski_list.h"

void eski_list_malloc_default_size_value_test(void)
{
	eski_List* list = NULL;

	list = eski_list_malloc(0);

	eski_assert(list != NULL);
	eski_assert(list->elements != NULL);
	eski_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eski_assert(list->position == 0);

	eski_list_free(list);
}

void eski_list_malloc_nondefault_size_value_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;

	list = eski_list_malloc(size);

	eski_assert(list != NULL);
	eski_assert(list->elements != NULL);
	eski_assert(list->size == size);
	eski_assert(list->position == 0);

	eski_list_free(list);
}

// void eski_list_add_null_element_value_test(void)
// {
// 	const size_t size = 16;
// 	eski_List* list = NULL;
// 	enum eski_List_Result addResult = FAILURE;
//
// 	list = eski_list_malloc(size);
//
// 	addResult = eski_list_add(NULL, list);
//
// 	eski_assert(addResult == FAILURE_NULL_ELEMENT);
// 	eski_assert(list->position == 0);
//
// 	eski_list_free(list);
// }

void eski_list_add_null_list_value_test(void)
{
	enum eski_List_Result addResult = FAILURE;

	addResult = eski_list_add(1001, NULL);

	eski_assert(addResult == FAILURE_NULL_LIST);
}

void eski_list_add_one_element_value_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;
	size_t element = 1001;
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(size);

	addResult = eski_list_add(element, list);

	eski_assert(addResult == SUCCESS);
	eski_assert(list->elements[0] == element);
	eski_assert(list->size == size);
	eski_assert(list->position == 1);

	eski_list_free(list);
}

void eski_list_add_until_size_expanded_value_test(void)
{
	const size_t size = 2;
	eski_List* list = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	size_t elementThree = 3003;
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(size);

	addResult = eski_list_add(elementOne, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(elementTwo, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(elementThree, list);
	eski_assert(addResult == SUCCESS);

	eski_assert(list->elements[0] == elementOne);
	eski_assert(list->elements[1] == elementTwo);
	eski_assert(list->elements[2] == elementThree);
	eski_assert(list->size == size * 2);
	eski_assert(list->position == 3);

	eski_list_free(list);
}

void eski_list_add_10_value_test(void)
{
	eski_List* list = NULL;
	size_t element = 1001;
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		addResult = eski_list_add(element, list);
		eski_assert(addResult == SUCCESS);
		eski_assert(list->elements[i] == element);
		element += 1001;
	}

	eski_assert(list->position == 10);

	eski_list_free(list);
}

void eski_list_release_value_tests(void)
{
	// eski_test_run("eski_list_add_null_element_value_test", eski_list_add_null_element_value_test);

	eski_test_run("eski_list_add_null_list_value_test", eski_list_add_null_list_value_test);
}

void eski_list_value_tests(void)
{
	#ifdef NDEBUG
		eski_list_release_value_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_list_malloc_default_size_value_test", eski_list_malloc_default_size_value_test);

	eski_test_run("eski_list_malloc_nondefault_size_value_test", eski_list_malloc_nondefault_size_value_test);

	eski_test_run("eski_list_add_one_element_value_test", eski_list_add_one_element_value_test);

	eski_test_run("eski_list_add_until_size_expanded_value_test", eski_list_add_until_size_expanded_value_test);

	eski_test_run("eski_list_add_10_value_test", eski_list_add_10_value_test);
}

