#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../eski_test.h"
#include "../eski_stack.h"

#define eski_TEST_STACK_SIZE 10

void eski_stack_malloc_test(void)
{
	eski_Stack* stack = NULL;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	eski_assert(stack != NULL);
	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == true);

	eski_stack_free(stack);
}

void eski_stack_push_empty_stack_test(void)
{
	eski_Stack* stack = NULL;
	size_t* element = NULL;
	enum eski_Stack_Result pushResult = FAILURE;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eski_stack_push(element, stack);

	eski_assert(pushResult == SUCCESS);
	eski_assert(stack->top == 0);
	eski_assert(*(size_t*)stack->elements[0] == *element);
	eski_assert(stack->isEmpty == false);

	free(element);
	eski_stack_free(stack);
}

void eski_stack_push_nonempty_stack_test(void)
{
	eski_Stack* stack = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	enum eski_Stack_Result pushResultOne = FAILURE;
	enum eski_Stack_Result pushResultTwo = FAILURE;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	elementOne = malloc(sizeof(size_t));
	elementTwo = malloc(sizeof(size_t));
	*elementOne = 1001;
	*elementTwo = 2002;

	pushResultOne = eski_stack_push(elementOne, stack);

	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == false);
	eski_assert(pushResultOne == SUCCESS);
	eski_assert(*(size_t*)stack->elements[0] == *elementOne);

	pushResultTwo = eski_stack_push(elementTwo, stack);

	eski_assert(stack->top == 1);
	eski_assert(stack->isEmpty == false);
	eski_assert(pushResultTwo == SUCCESS);
	eski_assert(*(size_t*)stack->elements[1] == *elementTwo);

	free(elementOne);
	free(elementTwo);
	eski_stack_free(stack);
}

void eski_stack_push_full_stack_test(void)
{
	eski_Stack* stack = NULL;
	size_t* element = NULL;
	enum eski_Stack_Result pushResult = FAILURE;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	/* set top to max to test overflow protection */
	stack->top = SIZE_MAX - 1;

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eski_stack_push(element, stack);

	eski_assert(pushResult == FAILURE_OVERFLOW_PROTECTION);

	free(element);
	eski_stack_free(stack);
}

void eski_stack_pop_empty_stack_test(void)
{
	eski_Stack* stack = NULL;
	void* poppedElement = NULL;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	poppedElement = eski_stack_pop(stack);

	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == true);
	eski_assert(poppedElement == NULL);

	eski_stack_free(stack);
}

void eski_stack_pop_test(void)
{
	eski_Stack* stack = NULL;
	size_t element = 1001;
	void* poppedElement = NULL;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	eski_stack_push(&element, stack);

	poppedElement = eski_stack_pop(stack);

	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == true);
	eski_assert(*(size_t*)poppedElement == element);

	eski_stack_free(stack);
}

void eski_stack_pop_multiple_test(void)
{
	eski_Stack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	void* poppedElementOne = NULL;
	void* poppedElementTwo = NULL;

	stack = eski_stack_malloc(eski_TEST_STACK_SIZE, sizeof(size_t*));

	eski_stack_push(&elementOne, stack);
	eski_stack_push(&elementTwo, stack);

	eski_assert(stack->top == 1);
	eski_assert(stack->isEmpty == false);

	poppedElementTwo = eski_stack_pop(stack);

	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == false);

	poppedElementOne = eski_stack_pop(stack);

	eski_assert(*(size_t*)poppedElementTwo == elementTwo);
	eski_assert(*(size_t*)poppedElementOne == elementOne);
	eski_assert(stack->top == 0);
	eski_assert(stack->isEmpty == true);

	eski_stack_free(stack);
}

void eski_stack_release_tests(void)
{
}

void eski_stack_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_stack_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_stack_malloc_test", eski_stack_malloc_test);

	eski_test_run("eski_stack_push_empty_stack_test", eski_stack_push_empty_stack_test);

	eski_test_run("eski_stack_push_nonempty_stack_test", eski_stack_push_nonempty_stack_test);

	eski_test_run("eski_stack_push_full_stack_test", eski_stack_push_full_stack_test);

	eski_test_run("eski_stack_pop_empty_stack_test", eski_stack_pop_empty_stack_test);

	eski_test_run("eski_stack_pop_test", eski_stack_pop_test);

	eski_test_run("eski_stack_pop_multiple_test", eski_stack_pop_multiple_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_stack_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
