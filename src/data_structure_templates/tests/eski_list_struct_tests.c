#include <stdlib.h>
#include <stdint.h>
#include "../../eski_test.h"

struct eski_Data
{
	uint32_t count;
	char* name;
};

#define eski_LIST_TYPE struct eski_Data
#include "../eski_list.h"

void eski_list_malloc_default_size_struct_test(void)
{
	eski_List* list = NULL;

	list = eski_list_malloc(0);

	eski_assert(list != NULL);
	eski_assert(list->elements != NULL);
	eski_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eski_assert(list->position == 0);

	eski_list_free(list);
}

void eski_list_malloc_nondefault_size_struct_test(void)
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

// void eski_list_add_null_element_struct_test(void)
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

void eski_list_add_null_list_struct_test(void)
{
	struct eski_Data data = { .count = 1, .name = "A" };
	enum eski_List_Result addResult = FAILURE;

	addResult = eski_list_add(data, NULL);

	eski_assert(addResult == FAILURE_NULL_LIST);
}

void eski_list_add_one_element_struct_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;
	struct eski_Data data = { .count = 1, .name = "A" };
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(size);

	addResult = eski_list_add(data, list);

	eski_assert(addResult == SUCCESS);
	eski_assert(list->elements[0].count == data.count);
	eski_assert(list->elements[0].name == data.name);
	eski_assert(list->size == size);
	eski_assert(list->position == 1);

	eski_list_free(list);
}

void eski_list_add_until_size_expanded_struct_test(void)
{
	const size_t size = 2;
	eski_List* list = NULL;
	struct eski_Data dataOne = { .count = 1, .name = "A" };
	struct eski_Data dataTwo = { .count = 2, .name = "AB" };
	struct eski_Data dataThree = { .count = 3, .name = "ABC" };
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(size);

	addResult = eski_list_add(dataOne, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(dataTwo, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(dataThree, list);
	eski_assert(addResult == SUCCESS);

	eski_assert(list->elements[0].count == dataOne.count);
	eski_assert(list->elements[0].name == dataOne.name);
	eski_assert(list->elements[1].count == dataTwo.count);
	eski_assert(list->elements[1].name == dataTwo.name);
	eski_assert(list->elements[2].count == dataThree.count);
	eski_assert(list->elements[2].name == dataThree.name);
	eski_assert(list->size == size * 2);
	eski_assert(list->position == 3);

	eski_list_free(list);
}

void eski_list_add_10_struct_test(void)
{
	eski_List* list = NULL;
	struct eski_Data dataOne = { .count = 1, .name = "A" };
	struct eski_Data dataTwo = { .count = 2, .name = "AB" };
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			addResult = eski_list_add(dataOne, list);
			eski_assert(addResult == SUCCESS);
			eski_assert(list->elements[i].count == dataOne.count);
			eski_assert(list->elements[i].name == dataOne.name);
		}
		else
		{
			addResult = eski_list_add(dataTwo, list);
			eski_assert(addResult == SUCCESS);
			eski_assert(list->elements[i].count == dataTwo.count);
			eski_assert(list->elements[i].name == dataTwo.name);
		}
	}

	eski_assert(list->position == 10);

	eski_list_free(list);

}

void eski_list_release_struct_tests(void)
{
	// eski_test_run("eski_list_add_null_element_struct_test", eski_list_add_null_element_struct_test);

	eski_test_run("eski_list_add_null_list_struct_test", eski_list_add_null_list_struct_test);
}

void eski_list_struct_tests(void)
{
	#ifdef NDEBUG
		eski_list_release_struct_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_list_malloc_default_size_struct_test", eski_list_malloc_default_size_struct_test);

	eski_test_run("eski_list_malloc_nondefault_size_struct_test", eski_list_malloc_nondefault_size_struct_test);

	eski_test_run("eski_list_add_one_element_struct_test", eski_list_add_one_element_struct_test);

	eski_test_run("eski_list_add_until_size_expanded_struct_test", eski_list_add_until_size_expanded_struct_test);

	eski_test_run("eski_list_add_10_struct_test", eski_list_add_10_struct_test);
}

