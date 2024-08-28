#include <stdlib.h>
#include <assert.h>
#include "eskilib_arraylist.h"
#include "eskilib_test.h"

void eskilib_arraylist_allocate_no_sizeOfElement_set_test()
{
	eskilib_ArrayList* arrayList = NULL;
	
	arrayList = eskilib_arraylist_allocate(0, 0); 
	
	assert(arrayList == NULL);
}

void eskilib_arraylist_allocate_default_size_test()
{
	eskilib_ArrayList* arrayList = NULL;
	size_t* element = NULL;

	element = malloc(sizeof(element));
	*element = 1001;
	
	arrayList = eskilib_arraylist_allocate(0, sizeof(element));
	
	assert(arrayList != NULL);
	assert(arrayList->Elements != NULL);
	assert(arrayList->Size > 0);/*just check greater than 0 so we don't depend on default size.*/
	assert(arrayList->Position == 0);

	free(element);
	eskilib_arraylist_free(arrayList);
}

void eskilib_arraylist_allocate_nondefault_size_test()
{
	const size_t size = 16;

	eskilib_ArrayList* arrayList = NULL;
	size_t* element = NULL;

	element = malloc(sizeof(element));
	*element = 1001;
	
	arrayList = eskilib_arraylist_allocate(size, sizeof(element));
	
	assert(arrayList != NULL);
	assert(arrayList->Elements != NULL);
	assert(arrayList->Size == size);
	assert(arrayList->Position == 0);

	free(element);
	eskilib_arraylist_free(arrayList);
}

void eskilib_arraylist_add_null_element_test()
{
	const size_t size = 16;

	eskilib_ArrayList* arrayList = NULL;
	bool addResult = false;
	
	arrayList = eskilib_arraylist_allocate(size, sizeof(size_t*));

	addResult = eskilib_arraylist_add(NULL, arrayList);
	
	assert(addResult == false);
	assert(arrayList->Position == 0);

	eskilib_arraylist_free(arrayList);
}

void eskilib_arraylist_add_null_arraylist_test()
{
	const size_t value = 1001;

	size_t* element = NULL;
	bool addResult = false;

	element = malloc(sizeof(element));
	*element = value;

	addResult = eskilib_arraylist_add(element, NULL);
	
	assert(addResult == false);

	free(element);
}

void eskilib_arraylist_add_one_element_test()
{
	const size_t value = 1001;
	const size_t size = 16;

	eskilib_ArrayList* arrayList = NULL;
	size_t* element = NULL;
	bool addResult = false;

	element = malloc(sizeof(element));
	*element = value;
	
	arrayList = eskilib_arraylist_allocate(size, sizeof(element));

	addResult = eskilib_arraylist_add(element, arrayList);
	
	assert(addResult == true);
	element = arrayList->Elements[0];
	assert(*element == value);
	assert(arrayList->Size == size);
	assert(arrayList->Position == 1);

	free(element);
	eskilib_arraylist_free(arrayList);
}

void eskilib_arraylist_add_until_size_expanded_test()
{
	const size_t valueOne = 1001;
	const size_t valueTwo = 2002;
	const size_t valueThree = 3003;
	const size_t size = 2;

	eskilib_ArrayList* arrayList = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	size_t* elementThree = NULL;
	bool addResult = false;

	elementOne = malloc(sizeof(elementOne));
	*elementOne = valueOne;
	elementTwo = malloc(sizeof(elementOne));
	*elementTwo = valueTwo;
	elementThree = malloc(sizeof(elementOne));
	*elementThree = valueThree;
	
	arrayList = eskilib_arraylist_allocate(size, sizeof(elementOne));

	addResult = eskilib_arraylist_add(elementOne, arrayList);
	assert(addResult == true);
	addResult = eskilib_arraylist_add(elementTwo, arrayList);
	assert(addResult == true);
	addResult = eskilib_arraylist_add(elementThree, arrayList);
	assert(addResult == true);
	
	elementOne = arrayList->Elements[0];
	assert(*elementOne == valueOne);
	elementTwo = arrayList->Elements[1];
	assert(*elementTwo == valueTwo);
	elementThree = arrayList->Elements[2];
	assert(*elementThree == valueThree);
	assert(arrayList->Size == size * 2);
	assert(arrayList->Position == 3);

	free(elementOne);
	free(elementTwo);
	free(elementThree);
	eskilib_arraylist_free(arrayList);
}


void eskilib_arraylist_tests()
{
	#ifdef NDEBUG
		eskilib_arraylist_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_arraylist_allocate_default_size_test", eskilib_arraylist_allocate_default_size_test);
	
	eskilib_test_run("eskilib_arraylist_allocate_nondefault_size_test", eskilib_arraylist_allocate_nondefault_size_test);
	
	eskilib_test_run("eskilib_arraylist_add_one_element_test", eskilib_arraylist_add_one_element_test);

	eskilib_test_run("eskilib_arraylist_add_until_size_expanded_test", eskilib_arraylist_add_until_size_expanded_test);
}

void eskilib_arraylist_release_tests()
{
	eskilib_test_run("eskilib_arraylist_allocate_no_sizeOfElement_set_test", eskilib_arraylist_allocate_no_sizeOfElement_set_test);

	eskilib_test_run("eskilib_arraylist_add_null_element_test", eskilib_arraylist_add_null_element_test);
	
	eskilib_test_run("eskilib_arraylist_add_null_arraylist_test", eskilib_arraylist_add_null_arraylist_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_arraylist_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
