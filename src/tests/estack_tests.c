#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../etest.h"
#include "../estack.h"

#define etest_STACK_SIZE 10

void estack_malloc_test(void)
{
	estack* stack = NULL;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	eassert(stack != NULL);
	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);

	estack_free(stack);
}

void estack_push_empty_stack_test(void)
{
	estack* stack = NULL;
	size_t* element = NULL;
	enum estack_Result pushResult = FAILURE;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = estack_push(element, stack);

	eassert(pushResult == SUCCESS);
	eassert(stack->top == 0);
	eassert(*(size_t*)stack->elements[0] == *element);
	eassert(stack->isEmpty == false);

	free(element);
	estack_free(stack);
}

void estack_push_nonempty_stack_test(void)
{
	estack* stack = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	enum estack_Result pushResultOne = FAILURE;
	enum estack_Result pushResultTwo = FAILURE;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	elementOne = malloc(sizeof(size_t));
	elementTwo = malloc(sizeof(size_t));
	*elementOne = 1001;
	*elementTwo = 2002;

	pushResultOne = estack_push(elementOne, stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == false);
	eassert(pushResultOne == SUCCESS);
	eassert(*(size_t*)stack->elements[0] == *elementOne);

	pushResultTwo = estack_push(elementTwo, stack);

	eassert(stack->top == 1);
	eassert(stack->isEmpty == false);
	eassert(pushResultTwo == SUCCESS);
	eassert(*(size_t*)stack->elements[1] == *elementTwo);

	free(elementOne);
	free(elementTwo);
	estack_free(stack);
}

void estack_push_full_stack_test(void)
{
	estack* stack = NULL;
	size_t* element = NULL;
	enum estack_Result pushResult = FAILURE;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	/* set top to max to test overflow protection */
	stack->top = SIZE_MAX - 1;

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = estack_push(element, stack);

	eassert(pushResult == FAILURE_OVERFLOW_PROTECTION);

	free(element);
	estack_free(stack);
}

void estack_pop_empty_stack_test(void)
{
	estack* stack = NULL;
	void* poppedElement = NULL;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	poppedElement = estack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);
	eassert(poppedElement == NULL);

	estack_free(stack);
}

void estack_pop_test(void)
{
	estack* stack = NULL;
	size_t element = 1001;
	void* poppedElement = NULL;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	estack_push(&element, stack);

	poppedElement = estack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);
	eassert(*(size_t*)poppedElement == element);

	estack_free(stack);
}

void estack_pop_multiple_test(void)
{
	estack* stack = NULL;
	size_t elementOne = 1001;
	size_t elementTwo = 2002;
	void* poppedElementOne = NULL;
	void* poppedElementTwo = NULL;

	stack = estack_malloc(etest_STACK_SIZE, sizeof(size_t*));

	estack_push(&elementOne, stack);
	estack_push(&elementTwo, stack);

	eassert(stack->top == 1);
	eassert(stack->isEmpty == false);

	poppedElementTwo = estack_pop(stack);

	eassert(stack->top == 0);
	eassert(stack->isEmpty == false);

	poppedElementOne = estack_pop(stack);

	eassert(*(size_t*)poppedElementTwo == elementTwo);
	eassert(*(size_t*)poppedElementOne == elementOne);
	eassert(stack->top == 0);
	eassert(stack->isEmpty == true);

	estack_free(stack);
}

void estack_tests(void)
{
	etest_start();

	etest_run(estack_malloc_test);
	etest_run(estack_push_empty_stack_test);
	etest_run(estack_push_nonempty_stack_test);
	etest_run(estack_push_full_stack_test);
	etest_run(estack_pop_empty_stack_test);
	etest_run(estack_pop_test);
	etest_run(estack_pop_multiple_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	estack_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
