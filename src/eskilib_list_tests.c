#include <stdlib.h>
#include <assert.h>
#include "eskilib_list.h"
#include "eskilib_test.h"

void eskilib_list_malloc_no_sizeOfElement_set_test()
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0, 0); 
	
	assert(list == NULL);
}

void eskilib_list_malloc_default_size_test()
{
	eskilib_List* list = NULL;
	size_t* element = NULL;

	element = malloc(sizeof(element));
	*element = 1001;
	
	list = eskilib_list_malloc(0, sizeof(element));
	
	assert(list != NULL);
	assert(list->elements != NULL);
	assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	assert(list->position == 0);

	free(element);
	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_test()
{
	const size_t size = 16;

	eskilib_List* list = NULL;
	size_t* element = NULL;

	element = malloc(sizeof(element));
	*element = 1001;
	
	list = eskilib_list_malloc(size, sizeof(element));
	
	assert(list != NULL);
	assert(list->elements != NULL);
	assert(list->size == size);
	assert(list->position == 0);

	free(element);
	eskilib_list_free(list);
}

void eskilib_list_add_null_element_test()
{
	const size_t size = 16;

	eskilib_List* list = NULL;
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size, sizeof(size_t*));

	addResult = eskilib_list_add(NULL, list);
	
	assert(addResult == FAILURE_NULL_ELEMENT);
	assert(list->position == 0);

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
	
	assert(addResult == FAILURE_NULL_LIST);

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
	
	assert(addResult == SUCCESS);
	element = list->elements[0];
	assert(*element == value);
	assert(list->size == size);
	assert(list->position == 1);

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
	assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementTwo, List);
	assert(addResult == SUCCESS);
	addResult = eskilib_list_add(elementThree, List);
	assert(addResult == SUCCESS);
	
	elementOne = List->elements[0];
	assert(*elementOne == valueOne);
	elementTwo = List->elements[1];
	assert(*elementTwo == valueTwo);
	elementThree = List->elements[2];
	assert(*elementThree == valueThree);
	assert(List->size == size * 2);
	assert(List->position == 3);

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
