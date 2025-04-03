#include <stdlib.h>
#include <stdint.h>
#include "../../etest.h"

struct eskilib_Data
{
	uint32_t count;
	char* name;
};

#define ELIST_TYPE struct eskilib_Data
#include "../elist.h"

void elist_malloc_default_size_struct_test(void)
{
	struct elist* list = NULL;

	list = elist_malloc(0);

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eassert(list->position == 0);

	elist_free(list);
}

void elist_malloc_nondefault_size_struct_test(void)
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

// void elist_add_null_element_struct_test(void)
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

void elist_add_null_list_struct_test(void)
{
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum elist_Result addResult = FAILURE;

	addResult = elist_add(data, NULL);

	eassert(addResult == FAILURE_NULL_LIST);
}

void elist_add_one_element_struct_test(void)
{
	const size_t size = 16;
	struct elist* list = NULL;
	struct eskilib_Data data = { .count = 1, .name = "A" };
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(size);

	addResult = elist_add(data, list);

	eassert(addResult == SUCCESS);
	eassert(list->elements[0].count == data.count);
	eassert(list->elements[0].name == data.name);
	eassert(list->size == size);
	eassert(list->position == 1);

	elist_free(list);
}

void elist_add_until_size_expanded_struct_test(void)
{
	const size_t size = 2;
	struct elist* list = NULL;
	struct eskilib_Data dataOne = { .count = 1, .name = "A" };
	struct eskilib_Data dataTwo = { .count = 2, .name = "AB" };
	struct eskilib_Data dataThree = { .count = 3, .name = "ABC" };
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(size);

	addResult = elist_add(dataOne, list);
	eassert(addResult == SUCCESS);
	addResult = elist_add(dataTwo, list);
	eassert(addResult == SUCCESS);
	addResult = elist_add(dataThree, list);
	eassert(addResult == SUCCESS);

	eassert(list->elements[0].count == dataOne.count);
	eassert(list->elements[0].name == dataOne.name);
	eassert(list->elements[1].count == dataTwo.count);
	eassert(list->elements[1].name == dataTwo.name);
	eassert(list->elements[2].count == dataThree.count);
	eassert(list->elements[2].name == dataThree.name);
	eassert(list->size == size * 2);
	eassert(list->position == 3);

	elist_free(list);
}

void elist_add_10_struct_test(void)
{
	struct elist* list = NULL;
	struct eskilib_Data dataOne = { .count = 1, .name = "A" };
	struct eskilib_Data dataTwo = { .count = 2, .name = "AB" };
	enum elist_Result addResult = FAILURE;

	list = elist_malloc(0);

	for (int i = 0; i < 10; i++)
	{
		if (i % 2 == 0)
		{
			addResult = elist_add(dataOne, list);
			eassert(addResult == SUCCESS);
			eassert(list->elements[i].count == dataOne.count);
			eassert(list->elements[i].name == dataOne.name);
		}
		else
		{
			addResult = elist_add(dataTwo, list);
			eassert(addResult == SUCCESS);
			eassert(list->elements[i].count == dataTwo.count);
			eassert(list->elements[i].name == dataTwo.name);
		}
	}

	eassert(list->position == 10);

	elist_free(list);

}

void elist_release_struct_tests(void)
{
	// etest_run(elist_add_null_element_struct_test);
	etest_run(elist_add_null_list_struct_test);
}

void elist_struct_tests(void)
{
	etest_start();

	#ifdef NDEBUG
		elist_release_struct_tests();
	#endif /* ifdef NDEBUG */

	etest_run(elist_malloc_default_size_struct_test);
	etest_run(elist_malloc_nondefault_size_struct_test);
	etest_run(elist_add_one_element_struct_test);
	etest_run(elist_add_until_size_expanded_struct_test);
	etest_run(elist_add_10_struct_test);

	etest_finish();
}
