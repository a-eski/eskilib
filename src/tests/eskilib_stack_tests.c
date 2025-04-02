#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../etest.h"
#include "../eskilib_stack.h"

#define etest_STACK_SIZE 10

void eskilib_stack_malloc_test(void)
{
	eskilib_Stack* stack = NULL;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	eassert(stack != NULL);
	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_empty_stack_test(void)
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	eassert(pushResult == SUCCESS);
	eassert(stack->top == 0);
	eassert(*(size_t*)stack->elements[0] == *element);
	eassert(stack->isEmpty == false);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_nonempty_stack_test(void)
{
	eskilib_Stack* stack = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	enum eskilib_Stack_Result pushResultOne = FAILURE;
	enum eskilib_Stack_Result pushResultTwo = FAILURE;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	elementOne = malloc(sizeof(size_t));
	elementTwo = malloc(sizeof(size_t));
	*elementOne = 1001;
	*elementTwo = 2002;

	pushResultOne = eskilib_stack_push(elementOne, stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == false);
	eassert(pushResultOne == SUCCESS);
	eassert(*(size_t*)stack->elements[0] == *elementOne);

	pushResultTwo = eskilib_stack_push(elementTwo, stack);

	eassert(stack->top == 1);
	eassert(stack->isEmpty == false);
	eassert(pushResultTwo == SUCCESS);
	eassert(*(size_t*)stack->elements[1] == *elementTwo);

	free(elementOne);
	free(elementTwo);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_full_stack_test(void)
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	enum eskilib_Stack_Result pushResult = FAILURE;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	/* set top to max to test overflow protection */
	stack->top = SIZE_MAX - 1;

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	eassert(pushResult == FAILURE_OVERFLOW_PROTECTION);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_pop_empty_stack_test(void)
{
	eskilib_Stack* stack = NULL;
	void* poppedElement = NULL;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	poppedElement = eskilib_stack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);
	eassert(poppedElement == NULL);

	eskilib_stack_free(stack);
}

void eskilib_stack_pop_test(void)
{
	eskilib_Stack* stack = NULL;
	size_t element = 1001;
	void* poppedElement = NULL;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	eskilib_stack_push(&element, stack);

	poppedElement = eskilib_stack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);
	eassert(*(size_t*)poppedElement == element);

	eskilib_stack_free(stack);
}

void eskilib_stack_pop_multiple_test(void)
{
	eskilib_Stack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	void* poppedElementOne = NULL;
	void* poppedElementTwo = NULL;

	stack = eskilib_stack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	eskilib_stack_push(&elementOne, stack);
	eskilib_stack_push(&elementTwo, stack);

	eassert(stack->top == 1);
	eassert(stack->isEmpty == false);

	poppedElementTwo = eskilib_stack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == false);

	poppedElementOne = eskilib_stack_pop(stack);

	eassert(*(size_t*)poppedElementTwo == elementTwo);
	eassert(*(size_t*)poppedElementOne == elementOne);
	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_tests(void)
{
	etest_start();

	etest_run(eskilib_stack_malloc_test);
	etest_run(eskilib_stack_push_empty_stack_test);
	etest_run(eskilib_stack_push_nonempty_stack_test);
	etest_run(eskilib_stack_push_full_stack_test);
	etest_run(eskilib_stack_pop_empty_stack_test);
	etest_run(eskilib_stack_pop_test);
	etest_run(eskilib_stack_pop_multiple_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	eskilib_stack_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
