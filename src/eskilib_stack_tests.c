#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eskilib_test.h"
#include "eskilib_stack.h"

#define ESKILIB_TEST_STACK_SIZE 10

void eskilib_stack_allocate_test()
{
	eskilib_Stack* stack = NULL;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	assert (stack != NULL);
	assert(stack->top == 0);
	assert(stack->isEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	assert(pushResult == SUCCESS);
	assert(stack->top == 0);
	assert(*(size_t*)stack->elements[0] == *element);
	assert(stack->isEmpty == false);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_nonempty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	enum eskilib_Stack_Result pushResultOne = FAILURE;
	enum eskilib_Stack_Result pushResultTwo = FAILURE;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	elementOne = malloc(sizeof(size_t));
	elementTwo = malloc(sizeof(size_t));
	*elementOne = 1001;
	*elementTwo = 2002;

	pushResultOne = eskilib_stack_push(elementOne, stack);

	assert(stack->top == 0);
	assert(stack->isEmpty == false);
	assert(pushResultOne == SUCCESS);
	assert(*(size_t*)stack->elements[0] == *elementOne);

	pushResultTwo = eskilib_stack_push(elementTwo, stack);

	assert(stack->top == 1);
	assert(stack->isEmpty == false);
	assert(pushResultTwo == SUCCESS);
	assert(*(size_t*)stack->elements[1] == *elementTwo);

	free(elementOne);
	free(elementTwo);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_full_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	/* set top to max to test overflow protection */
	stack->top = SIZE_MAX - 1;

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	assert(pushResult == FAILURE_OVERFLOW_PROTECTION);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_pop_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	void* poppedElement = NULL;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	poppedElement = eskilib_stack_pop(stack);

	assert(stack->top == 0);
	assert(stack->isEmpty == true);
	assert(poppedElement == NULL);

	eskilib_stack_free(stack);
}

void eskilib_stack_pop_test()
{
	eskilib_Stack* stack = NULL;
	size_t element = 1001;
	void* poppedElement = NULL;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	eskilib_stack_push(&element, stack);

	poppedElement = eskilib_stack_pop(stack);

	assert(stack->top == 0);
	assert(stack->isEmpty == true);
	assert(*(size_t*)poppedElement == element);
	
	eskilib_stack_free(stack);
}

void eskilib_stack_pop_multiple_test()
{
	eskilib_Stack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	void* poppedElementOne = NULL;
	void* poppedElementTwo = NULL;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	eskilib_stack_push(&elementOne, stack);
	eskilib_stack_push(&elementTwo, stack);

	assert(stack->top == 1);
	assert(stack->isEmpty == false);

	poppedElementTwo = eskilib_stack_pop(stack);

	assert(stack->top == 0);
	assert(stack->isEmpty == false);

	poppedElementOne = eskilib_stack_pop(stack);

	assert(*(size_t*)poppedElementTwo == elementTwo);
	assert(*(size_t*)poppedElementOne == elementOne);
	assert(stack->top == 0);
	assert(stack->isEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_release_tests()
{
}

void eskilib_stack_tests()
{
	#ifdef NDEBUG
		eskilib_stack_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_stack_allocate_test", eskilib_stack_allocate_test);

	eskilib_test_run("eskilib_stack_push_empty_stack_test", eskilib_stack_push_empty_stack_test);

	eskilib_test_run("eskilib_stack_push_nonempty_stack_test", eskilib_stack_push_nonempty_stack_test);

	eskilib_test_run("eskilib_stack_push_full_stack_test", eskilib_stack_push_full_stack_test);
	
	eskilib_test_run("eskilib_stack_pop_empty_stack_test", eskilib_stack_pop_empty_stack_test);

	eskilib_test_run("eskilib_stack_pop_test", eskilib_stack_pop_test);

	eskilib_test_run("eskilib_stack_pop_multiple_test", eskilib_stack_pop_multiple_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_stack_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
