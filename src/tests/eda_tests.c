#include <stdlib.h>
#include "../eda.h"
#include "../etest.h"

void eda_malloc_no_sizeOfElement_set_test(void)
{
	eda* list = NULL;

	list = eda_malloc(0, 0);

	eassert(list == NULL);
}

void eda_malloc_default_size_test(void)
{
	eda* list = NULL;

	list = eda_malloc(0, sizeof(size_t));

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eassert(list->position == 0);

	eda_free(list);
}

void eda_malloc_nondefault_size_test(void)
{
	const size_t size = 16;
	eda* list = NULL;

	list = eda_malloc(size, sizeof(size_t));

	eassert(list != NULL);
	eassert(list->elements != NULL);
	eassert(list->size == size);
	eassert(list->position == 0);

	eda_free(list);
}

void eda_add_null_element_test(void)
{
	const size_t size = 16;
	eda* list = NULL;
	enum eda_Result addResult = FAILURE;

	list = eda_malloc(size, sizeof(size_t*));

	addResult = eda_add(NULL, list);

	eassert(addResult == FAILURE_NULL_ELEMENT);
	eassert(list->position == 0);

	eda_free(list);
}

void eda_add_null_list_test(void)
{
	size_t* element = NULL;
	enum eda_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;

	addResult = eda_add(element, NULL);

	eassert(addResult == FAILURE_NULL_LIST);

	free(element);
}

void eda_add_one_element_test(void)
{
	const size_t size = 16;
	eda* list = NULL;
	size_t* element = NULL;
	enum eda_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = 1001;

	list = eda_malloc(size, sizeof(element));

	addResult = eda_add(element, list);

	eassert(addResult == SUCCESS);
	eassert(*(size_t*)list->elements[0] == *element);
	eassert(list->size == size);
	eassert(list->position == 1);

	free(element);
	eda_free(list);
}

void eda_add_until_size_expanded_test(void)
{
	const size_t size = 2;
	eda* list = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	size_t* elementThree = NULL;
	enum eda_Result addResult = FAILURE;

	elementOne = malloc(sizeof(elementOne));
	*elementOne = 1001;
	elementTwo = malloc(sizeof(elementOne));
	*elementTwo = 2002;
	elementThree = malloc(sizeof(elementOne));
	*elementThree = 3003;

	list = eda_malloc(size, sizeof(elementOne));

	addResult = eda_add(elementOne, list);
	eassert(addResult == SUCCESS);
	addResult = eda_add(elementTwo, list);
	eassert(addResult == SUCCESS);
	addResult = eda_add(elementThree, list);
	eassert(addResult == SUCCESS);

	eassert(*(size_t*)list->elements[0] == *elementOne);
	eassert(*(size_t*)list->elements[1] == *elementTwo);
	eassert(*(size_t*)list->elements[2] == *elementThree);
	eassert(list->size == size * 2);
	eassert(list->position == 3);

	free(elementOne);
	free(elementTwo);
	free(elementThree);
	eda_free(list);
}

void eda_release_tests(void)
{
	etest_run(eda_malloc_no_sizeOfElement_set_test);
	etest_run(eda_add_null_element_test);
	etest_run(eda_add_null_list_test);
}

void eda_tests(void)
{
	etest_start();

	#ifdef NDEBUG
		eda_release_tests();
	#endif /* ifdef NDEBUG */

	etest_run(eda_malloc_default_size_test);
	etest_run(eda_malloc_nondefault_size_test);
	etest_run(eda_add_one_element_test);
	etest_run(eda_add_until_size_expanded_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	eda_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
