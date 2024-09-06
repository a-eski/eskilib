#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "eskilib_test.h"

struct eskilib_String
{
	uint32_t length;
	char* value;
};

#define eskilib_List_TYPE struct eskilib_String
#include "eskilib_list.h"

void eskilib_list_malloc_default_size_test()
{
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(0);
	
	assert(list != NULL);
	assert(list->elements != NULL);
	assert(list->size > 0);/*just check greater than 0 so we don't depend on default size.*/
	assert(list->position == 0);

	eskilib_list_free(list);
}

void eskilib_list_malloc_nondefault_size_test()
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	
	list = eskilib_list_malloc(size);
	
	assert(list != NULL);
	assert(list->elements != NULL);
	assert(list->size == size);
	assert(list->position == 0);

	eskilib_list_free(list);
}

// void eskilib_list_add_null_element_test()
// {
// 	const size_t size = 16;
// 	eskilib_List* list = NULL;
// 	enum eskilib_List_Result addResult = FAILURE;
// 	
// 	list = eskilib_list_malloc(size);
//
// 	addResult = eskilib_list_add(NULL, list);
// 	
// 	assert(addResult == FAILURE_NULL_ELEMENT);
// 	assert(list->position == 0);
//
// 	eskilib_list_free(list);
// }

void eskilib_list_add_null_list_test()
{
	struct eskilib_String message = { .value = "Encoded message", .length = 15 };
	enum eskilib_List_Result addResult = FAILURE;

	addResult = eskilib_list_add(message, NULL);
	
	assert(addResult == FAILURE_NULL_LIST);
}

void eskilib_list_add_one_element_test()
{
	const size_t size = 16;
	eskilib_List* list = NULL;
	struct eskilib_String message = { .value = "Encoded message", .length = 15 };
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(message, list);
	
	assert(addResult == SUCCESS);
	assert(list->elements[0].length == message.length);
	assert(list->elements[0].value == message.value);
	assert(list->size == size);
	assert(list->position == 1);

	eskilib_list_free(list);
}

void eskilib_list_add_until_size_expanded_test()
{
	const size_t size = 2;
	eskilib_List* list = NULL;
	struct eskilib_String messageOne = { .value = "Encoded message 1", .length = 17 };
	struct eskilib_String messageTwo = { .value = "Encoded message 12", .length = 18 };
	struct eskilib_String messageThree = { .value = "Encoded message 123", .length = 19 };
	enum eskilib_List_Result addResult = FAILURE;
	
	list = eskilib_list_malloc(size);

	addResult = eskilib_list_add(messageOne, list);
	assert(addResult == SUCCESS);
	addResult = eskilib_list_add(messageTwo, list);
	assert(addResult == SUCCESS);
	addResult = eskilib_list_add(messageThree, list);
	assert(addResult == SUCCESS);
	
	assert(list->elements[0].length == messageOne.length);
	assert(list->elements[0].value == messageOne.value);
	assert(list->elements[1].length == messageTwo.length);
	assert(list->elements[1].value == messageTwo.value);
	assert(list->elements[2].length == messageThree.length);
	assert(list->elements[2].value == messageThree.value);
	assert(list->size == size * 2);
	assert(list->position == 3);

	eskilib_list_free(list);
}

void eskilib_list_struct_release_tests()
{
	// eskilib_test_run("eskilib_list_add_null_element_test", eskilib_list_add_null_element_test);
	
	eskilib_test_run("eskilib_list_add_null_list_test", eskilib_list_add_null_list_test);
}

void eskilib_list_struct_tests()
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
	eskilib_list_struct_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
