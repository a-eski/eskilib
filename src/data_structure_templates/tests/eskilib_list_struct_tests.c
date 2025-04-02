#include <stdlib.h>
#include <stdint.h>
#include "../../etest.h"

struct eskilib_Data
{
	uint32_t count;
	char* name;
};

#define ESKILIB_LIST_TYPE struct eskilib_Data
#include "../eskilib_list.h"

void eskilib_list_malloc_default_size_struct_test(void)
{
	struct eskilib_List* list = NULL;

	list = eskilib_list_malloc(0);

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eassert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_struct_test(void)
{
	const size_t size = 16;
	struct eskilib_List* list = NULL;

	list = eskilib_list_malloc(size);

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size == size);
	eassert(list->position == 0);

	eskilib_list_free(list);
}

// void eskilib_list_add_null_element_struct_test(void)
// {
// 	const size_t size = 16;
// 	eskilib_List* list = NULL;
// 	enum eskilib_List_Result addResult = FAILURE;
//
// 	list = eskilib_list_malloc(size);
//
// 	addResult = eskilib_list_add(NULL, list);
//
// 	eassert(addResult == FAILURE_NULL_ELEMENT);
// 	eassert(list->position == 0);
//
// 	eskilib_list_free(list);
// }

void eskilib_list_add_null_list_struct_test(void)
{
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum eskilib_List_Result addResult = FAILURE;

	addResult = eskilib_list_add(data, NULL);

	eassert(addResult == FAILURE_NULL_LIST);
}

void eskilib_list_add_one_element_struct_test(void)
{
	const size_t size = 16;
	struct eskilib_List* list = NULL;
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum eskilib_List_Result addResult = FAILURE;

	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(data, list);

	eassert(addResult == SUCCESS);
	eassert(list->elements[0].count == data.count);
	eassert(list->elements[0].name == data.name);
	eassert(list->size == size);
	eassert(list->position == 1);

	eskilib_list_free(list);
}

void eskilib_list_add_until_size_expanded_struct_test(void)
{
	const size_t size = 2;
	struct eskilib_List* list = NULL;
	struct eskilib_Data dataOne = { .count = 1, .name = "A" };
	struct eskilib_Data dataTwo = { .count = 2, .name = "AB" };
	struct eskilib_Data dataThree = { .count = 3, .name = "ABC" };
	enum eskilib_List_Result addResult = FAILURE;

	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(dataOne, list);
	eassert(addResult == SUCCESS);
	addResult = eskilib_list_add(dataTwo, list);
	eassert(addResult == SUCCESS);
	addResult = eskilib_list_add(dataThree, list);
	eassert(addResult == SUCCESS);

	eassert(list->elements[0].count == dataOne.count);
	eassert(list->elements[0].name == dataOne.name);
	eassert(list->elements[1].count == dataTwo.count);
	eassert(list->elements[1].name == dataTwo.name);
	eassert(list->elements[2].count == dataThree.count);
	eassert(list->elements[2].name == dataThree.name);
	eassert(list->size == size * 2);
	eassert(list->position == 3);

	eskilib_list_free(list);
}

void eskilib_list_add_10_struct_test(void)
{
	struct eskilib_List* list = NULL;
	struct eskilib_Data dataOne = { .count = 1, .name = "A" };
	struct eskilib_Data dataTwo = { .count = 2, .name = "AB" };
	enum eskilib_List_Result addResult = FAILURE;

	list = eskilib_list_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			addResult = eskilib_list_add(dataOne, list);
			eassert(addResult == SUCCESS);
			eassert(list->elements[i].count == dataOne.count);
			eassert(list->elements[i].name == dataOne.name);
		}
		else
		{
			addResult = eskilib_list_add(dataTwo, list);
			eassert(addResult == SUCCESS);
			eassert(list->elements[i].count == dataTwo.count);
			eassert(list->elements[i].name == dataTwo.name);
		}
	}

	eassert(list->position == 10);

	eskilib_list_free(list);

}

void eskilib_list_release_struct_tests(void)
{
	// etest_run(eskilib_list_add_null_element_struct_test);
	etest_run(eskilib_list_add_null_list_struct_test);
}

void eskilib_list_struct_tests(void)
{
	etest_start();

	#ifdef NDEBUG
		eskilib_list_release_struct_tests();
	#endif /* ifdef NDEBUG */

	etest_run(eskilib_list_malloc_default_size_struct_test);
	etest_run(eskilib_list_malloc_nondefault_size_struct_test);
	etest_run(eskilib_list_add_one_element_struct_test);
	etest_run(eskilib_list_add_until_size_expanded_struct_test);
	etest_run(eskilib_list_add_10_struct_test);

	etest_finish();
}
