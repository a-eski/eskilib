#include <stdlib.h>
#include <stdint.h>
#include "../../eskilib_test.h"

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

	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_struct_test(void)
{
	const size_t size = 16;
	struct eskilib_List* list = NULL;

	list = eskilib_list_malloc(size);

	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 0);

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
// 	eskilib_assert(addResult == FAILURE_NULL_ELEMENT);
// 	eskilib_assert(list->position == 0);
//
// 	eskilib_list_free(list);
// }

void eskilib_list_add_null_list_struct_test(void)
{
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum eskilib_List_Result addResult = FAILURE;

	addResult = eskilib_list_add(data, NULL);

	eskilib_assert(addResult == FAILURE_NULL_LIST);
}

void eskilib_list_add_one_element_struct_test(void)
{
	const size_t size = 16;
	struct eskilib_List* list = NULL;
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum eskilib_List_Result addResult = FAILURE;

	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(data, list);

	eskilib_assert(addResult == SUCCESS);
	eskilib_assert(list->elements[0].count == data.count);
	eskilib_assert(list->elements[0].name == data.name);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 1);

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
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(dataTwo, list);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(dataThree, list);
	eskilib_assert(addResult == SUCCESS);

	eskilib_assert(list->elements[0].count == dataOne.count);
	eskilib_assert(list->elements[0].name == dataOne.name);
	eskilib_assert(list->elements[1].count == dataTwo.count);
	eskilib_assert(list->elements[1].name == dataTwo.name);
	eskilib_assert(list->elements[2].count == dataThree.count);
	eskilib_assert(list->elements[2].name == dataThree.name);
	eskilib_assert(list->size == size * 2);
	eskilib_assert(list->position == 3);

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
			eskilib_assert(addResult == SUCCESS);
			eskilib_assert(list->elements[i].count == dataOne.count);
			eskilib_assert(list->elements[i].name == dataOne.name);
		}
		else
		{
			addResult = eskilib_list_add(dataTwo, list);
			eskilib_assert(addResult == SUCCESS);
			eskilib_assert(list->elements[i].count == dataTwo.count);
			eskilib_assert(list->elements[i].name == dataTwo.name);
		}
	}

	eskilib_assert(list->position == 10);

	eskilib_list_free(list);

}

void eskilib_list_release_struct_tests(void)
{
	// eskilib_test_run(eskilib_list_add_null_element_struct_test);

	eskilib_test_run(eskilib_list_add_null_list_struct_test);
}

void eskilib_list_struct_tests(void)
{
	#ifdef NDEBUG
		eskilib_list_release_struct_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run(eskilib_list_malloc_default_size_struct_test);

	eskilib_test_run(eskilib_list_malloc_nondefault_size_struct_test);

	eskilib_test_run(eskilib_list_add_one_element_struct_test);

	eskilib_test_run(eskilib_list_add_until_size_expanded_struct_test);

	eskilib_test_run(eskilib_list_add_10_struct_test);
}

