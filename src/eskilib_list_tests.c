#include <stdlib.h>
#include "eskilib_list.h"
#include "eskilib_test.h"

void eskilib_list_malloc_no_sizeOfElement_set_test()
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0, 0); 
	
	eskilib_assert(list == NULL);
}

void eskilib_list_malloc_default_size_test()
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0, sizeof(size_t));
	
	eskilib_assert(list != NULL);
	eskilib_assert(list->elements != NULL);
	eskilib_assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	eskilib_assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_test()
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

void eskilib_list_add_null_element_test()
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

void eskilib_list_add_null_list_test()
{
	const size_t value = 1001;
	size_t* element = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = value;

	addResult = eskilib_list_add(element, NULL);
	
	eskilib_assert(addResult == FAILURE_NULL_LIST);

	free(element);
}

void eskilib_list_add_one_element_test()
{
	const size_t value = 1001;
	const size_t size = 16;

	eskilib_List* list = NULL;
	size_t* element = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	element = malloc(sizeof(element));
	*element = value;
	
	list = eskilib_list_malloc(size, sizeof(element));

	addResult = eskilib_list_add(element, list);
	
	eskilib_assert(addResult == SUCCESS);
	element = list->elements[0];
	eskilib_assert(*element == value);
	eskilib_assert(list->size == size);
	eskilib_assert(list->position == 1);

	free(element);
	eskilib_list_free(list);
}

void eskilib_list_add_until_size_expanded_test()
{
	const size_t valueOne = 1001;
	const size_t valueTwo = 2002;
	const size_t valueThree = 3003;
	const size_t size = 2;

	eskilib_List* List = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	size_t* elementThree = NULL;
	enum eskilib_List_Result addResult = FAILURE;

	elementOne = malloc(sizeof(elementOne));
	*elementOne = valueOne;
	elementTwo = malloc(sizeof(elementOne));
	*elementTwo = valueTwo;
	elementThree = malloc(sizeof(elementOne));
	*elementThree = valueThree;
	
	List = eskilib_list_malloc(size, sizeof(elementOne));

	addResult = eskilib_list_add(elementOne, List);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementTwo, List);
	eskilib_assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementThree, List);
	eskilib_assert(addResult == SUCCESS);
	
	elementOne = List->elements[0];
	eskilib_assert(*elementOne == valueOne);
	elementTwo = List->elements[1];
	eskilib_assert(*elementTwo == valueTwo);
	elementThree = List->elements[2];
	eskilib_assert(*elementThree == valueThree);
	eskilib_assert(List->size == size * 2);
	eskilib_assert(List->position == 3);

	free(elementOne);
	free(elementTwo);
	free(elementThree);
	eskilib_list_free(List);
}

void eskilib_list_release_tests()
{
	eskilib_test_run("eskilib_list_malloc_no_sizeOfElement_set_test", eskilib_list_malloc_no_sizeOfElement_set_test);

	eskilib_test_run("eskilib_list_add_null_element_test", eskilib_list_add_null_element_test);
	
	eskilib_test_run("eskilib_list_add_null_list_test", eskilib_list_add_null_list_test);
}

void eskilib_list_tests()
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
