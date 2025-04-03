#include <stdlib.h>
#include "../../etest.h"

#define ELIST_TYPE size_t
#include "../elist.h"

void elist_malloc_default_size_value_test(void)
{
	struct elist* list = NULL;

	list = elist_malloc(0);

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eassert(list->position == 0);

	elist_free(list);
}

void elist_malloc_nondefault_size_value_test(void)
{
	const size_t size = 16;
	struct elist* list = NULL;

	list = elist_malloc(size);

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size == size);
	eassert(list->position == 0);

	elist_free(list);
}

// void elist_add_null_element_value_test(void)
// {
// 	const size_t size = 16;
// 	elist* list = NULL;
// 	enum elist_Result addResult = FAILURE;
//
// 	list = elist_malloc(size);
//
// 	addResult = elist_add(NULL, list);
//
// 	eassert(addResult == FAILURE_NULL_ELEMENT);
// 	eassert(list->position == 0);
//
// 	elist_free(list);
// }

void elist_add_null_list_value_test(void)
{
	enum elist_Result addResult = FAILURE;

	addResult = elist_add(1001, NULL);

	eassert(addResult == FAILURE_NULL_LIST);
}

void elist_add_one_element_value_test(void)
{
	const size_t size = 16;
	struct elist* list = NULL;
	size_t element = 1001;
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(size);

	addResult = elist_add(element, list);

	eassert(addResult == SUCCESS);
	eassert(list->elements[0] == element);
	eassert(list->size == size);
	eassert(list->position == 1);

	elist_free(list);
}

void elist_add_until_size_expanded_value_test(void)
{
	const size_t size = 2;
	struct elist* list = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	size_t elementThree = 3003;
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(size);

	addResult = elist_add(elementOne, list);
	eassert(addResult == SUCCESS);
	addResult = elist_add(elementTwo, list);
	eassert(addResult == SUCCESS);
	addResult = elist_add(elementThree, list);
	eassert(addResult == SUCCESS);

	eassert(list->elements[0] == elementOne);
	eassert(list->elements[1] == elementTwo);
	eassert(list->elements[2] == elementThree);
	eassert(list->size == size * 2);
	eassert(list->position == 3);

	elist_free(list);
}

void elist_add_10_value_test(void)
{
	struct elist* list = NULL;
	size_t element = 1001;
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		addResult = elist_add(element, list);
		eassert(addResult == SUCCESS);
		eassert(list->elements[i] == element);
		element += 1001;
	}

	eassert(list->position == 10);

	elist_free(list);
}

void elist_release_value_tests(void)
{
	// etest_run("elist_add_null_element_value_test", elist_add_null_element_value_test);
	etest_run(elist_add_null_list_value_test);
}

void elist_value_tests(void)
{
	etest_start();

	#ifdef NDEBUG
		elist_release_value_tests();
	#endif /* ifdef NDEBUG */

	etest_run(elist_malloc_default_size_value_test);
	etest_run(elist_malloc_nondefault_size_value_test);
	etest_run(elist_add_one_element_value_test);
	etest_run(elist_add_until_size_expanded_value_test);
	etest_run(elist_add_10_value_test);

	etest_finish();
}
