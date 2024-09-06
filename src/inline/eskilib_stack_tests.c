#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "eskilib_test.h"

#define eskilib_Stack_TYPE size_t
#include "eskilib_stack.h"

#define ESKILIB_TEST_STACK_SIZE 10

void eskilib_stack_malloc_test()
{
	eskilib_Stack* stack = NULL;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	eskilib_assert(stack != NULL);
	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t element = 1001;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	pushResult = eskilib_stack_push(element, stack);

	eskilib_assert(pushResult == SUCCESS);
	eskilib_assert(stack->top == 0);
	eskilib_assert(*(size_t*)stack->elements[0] == element);
	eskilib_assert(stack->isEmpty == false);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_nonempty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	enum eskilib_Stack_Result pushResultOne = FAILURE;
	enum eskilib_Stack_Result pushResultTwo = FAILURE;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	pushResultOne = eskilib_stack_push(elementOne, stack);

	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == false);
	eskilib_assert(pushResultOne == SUCCESS);
	eskilib_assert(*(size_t*)stack->elements[0] == elementOne);

	pushResultTwo = eskilib_stack_push(elementTwo, stack);

	eskilib_assert(stack->top == 1);
	eskilib_assert(stack->isEmpty == false);
	eskilib_assert(pushResultTwo == SUCCESS);
	eskilib_assert(*(size_t*)stack->elements[1] == elementTwo);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_full_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t element = 1001;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	/* set top to max to test overflow protection */
	stack->top = SIZE_MAX - 1;

	pushResult = eskilib_stack_push(element, stack);

	eskilib_assert(pushResult == FAILURE_OVERFLOW_PROTECTION);

	eskilib_stack_free(stack);
}

void eskilib_stack_pop_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t poppedElement = 0;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	poppedElement = eskilib_stack_pop(stack);

	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == true);
	eskilib_assert(poppedElement == (size_t)NULL);

	eskilib_stack_free(stack);
}

void eskilib_stack_pop_test()
{
	eskilib_Stack* stack = NULL;
	size_t element = 1001;
	size_t poppedElement = 0;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	eskilib_stack_push(element, stack);

	poppedElement = eskilib_stack_pop(stack);

	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == true);
	eskilib_assert(*(size_t*)poppedElement == element);
	
	eskilib_stack_free(stack);
}

void eskilib_stack_pop_multiple_test()
{
	eskilib_Stack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	size_t poppedElementOne = 0;
	size_t poppedElementTwo = 0;

	stack = eskilib_stack_malloc(ESKILIB_TEST_STACK_SIZE);

	eskilib_stack_push(elementOne, stack);
	eskilib_stack_push(elementTwo, stack);

	eskilib_assert(stack->top == 1);
	eskilib_assert(stack->isEmpty == false);

	poppedElementTwo = eskilib_stack_pop(stack);

	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == false);

	poppedElementOne = eskilib_stack_pop(stack);

	eskilib_assert(*(size_t*)poppedElementTwo == elementTwo);
	eskilib_assert(*(size_t*)poppedElementOne == elementOne);
	eskilib_assert(stack->top == 0);
	eskilib_assert(stack->isEmpty == true);

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

	eskilib_test_run("eskilib_stack_malloc_test", eskilib_stack_malloc_test);

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
