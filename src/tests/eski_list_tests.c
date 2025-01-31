#include <stdlib.h>
#include "../eski_list.h"
#include "../eski_test.h"

void eski_list_malloc_no_sizeOfElement_set_test(void)
{
	eski_List* list = NULL;

	list = eski_list_malloc(0, 0);

	eski_assert(list == NULL);
}

void eski_list_malloc_default_size_test(void)
{
	eski_List* list = NULL;

	list = eski_list_malloc(0, sizeof(size_t));

	eski_assert(list != NULL);
	eski_assert(list->elements != NULL);
	eski_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eski_assert(list->position == 0);

	eski_list_free(list);
}

void eski_list_malloc_nondefault_size_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;

	list = eski_list_malloc(size, sizeof(size_t));

	eski_assert(list != NULL);
	eski_assert(list->elements != NULL);
	eski_assert(list->size == size);
	eski_assert(list->position == 0);

	eski_list_free(list);
}

void eski_list_add_null_element_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;
	enum eski_List_Result addResult = FAILURE;

	list = eski_list_malloc(size, sizeof(size_t*));

	addResult = eski_list_add(NULL, list);

	eski_assert(addResult == FAILURE_NULL_ELEMENT);
	eski_assert(list->position == 0);

	eski_list_free(list);
}

void eski_list_add_null_list_test(void)
{
	size_t* element = NULL;
	enum eski_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;

	addResult = eski_list_add(element, NULL);

	eski_assert(addResult == FAILURE_NULL_LIST);

	free(element);
}

void eski_list_add_one_element_test(void)
{
	const size_t size = 16;
	eski_List* list = NULL;
	size_t* element = NULL;
	enum eski_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;

	list = eski_list_malloc(size, sizeof(element));

	addResult = eski_list_add(element, list);

	eski_assert(addResult == SUCCESS);
	eski_assert(*(size_t*)list->elements[0] == *element);
	eski_assert(list->size == size);
	eski_assert(list->position == 1);

	free(element);
	eski_list_free(list);
}

void eski_list_add_until_size_expanded_test(void)
{
	const size_t size = 2;
	eski_List* list = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	size_t* elementThree = NULL;
	enum eski_List_Result addResult = FAILURE;

	elementOne = malloc(sizeof(elementOne));
	*elementOne = 1001;
	elementTwo = malloc(sizeof(elementOne));
	*elementTwo = 2002;
	elementThree = malloc(sizeof(elementOne));
	*elementThree = 3003;

	list = eski_list_malloc(size, sizeof(elementOne));

	addResult = eski_list_add(elementOne, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(elementTwo, list);
	eski_assert(addResult == SUCCESS);
	addResult = eski_list_add(elementThree, list);
	eski_assert(addResult == SUCCESS);

	eski_assert(*(size_t*)list->elements[0] == *elementOne);
	eski_assert(*(size_t*)list->elements[1] == *elementTwo);
	eski_assert(*(size_t*)list->elements[2] == *elementThree);
	eski_assert(list->size == size * 2);
	eski_assert(list->position == 3);

	free(elementOne);
	free(elementTwo);
	free(elementThree);
	eski_list_free(list);
}

void eski_list_release_tests(void)
{
	eski_test_run("eski_list_malloc_no_sizeOfElement_set_test", eski_list_malloc_no_sizeOfElement_set_test);

	eski_test_run("eski_list_add_null_element_test", eski_list_add_null_element_test);

	eski_test_run("eski_list_add_null_list_test", eski_list_add_null_list_test);
}

void eski_list_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_list_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_list_malloc_default_size_test", eski_list_malloc_default_size_test);

	eski_test_run("eski_list_malloc_nondefault_size_test", eski_list_malloc_nondefault_size_test);

	eski_test_run("eski_list_add_one_element_test", eski_list_add_one_element_test);

	eski_test_run("eski_list_add_until_size_expanded_test", eski_list_add_until_size_expanded_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_list_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
