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
	assert(stack->Top == 0);
	assert(stack->IsEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_push_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	bool pushResult = false;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	assert(pushResult == true);
	assert(stack->Top == 0);
	assert(*(size_t*)stack->Elements[0] == *element);
	assert(stack->IsEmpty == false);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_nonempty_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* elementOne = NULL;
	size_t* elementTwo = NULL;
	bool pushResultOne = false;
	bool pushResultTwo = false;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	elementOne = malloc(sizeof(size_t));
	elementTwo = malloc(sizeof(size_t));
	*elementOne = 1001;
	*elementTwo = 2002;

	pushResultOne = eskilib_stack_push(elementOne, stack);

	assert(stack->Top == 0);
	assert(stack->IsEmpty == false);
	assert(pushResultOne == true);
	assert(*(size_t*)stack->Elements[0] == *elementOne);

	pushResultTwo = eskilib_stack_push(elementTwo, stack);

	assert(stack->Top == 1);
	assert(stack->IsEmpty == false);
	assert(pushResultTwo == true);
	assert(*(size_t*)stack->Elements[1] == *elementTwo);

	free(elementOne);
	free(elementTwo);
	eskilib_stack_free(stack);
}

void eskilib_stack_push_full_stack_test()
{
	eskilib_Stack* stack = NULL;
	size_t* element = NULL;
	bool pushResult = false;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	/* set top to max to test overflow protection */
	stack->Top = SIZE_MAX - 1;

	element = malloc(sizeof(size_t));
	*element = 1001;

	pushResult = eskilib_stack_push(element, stack);

	assert(pushResult == false);

	free(element);
	eskilib_stack_free(stack);
}

void eskilib_stack_pop_empty_stack_test()
{
	eskilib_Stack* stack = NULL;
	void* poppedElement = NULL;

	stack = eskilib_stack_allocate(ESKILIB_TEST_STACK_SIZE, sizeof(size_t*));

	poppedElement = eskilib_stack_pop(stack);

	assert(stack->Top == 0);
	assert(stack->IsEmpty == true);
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

	assert(stack->Top == 0);
	assert(stack->IsEmpty == true);
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

	assert(stack->Top == 1);
	assert(stack->IsEmpty == false);

	poppedElementTwo = eskilib_stack_pop(stack);

	assert(stack->Top == 0);
	assert(stack->IsEmpty == false);

	poppedElementOne = eskilib_stack_pop(stack);

	assert(*(size_t*)poppedElementTwo == elementTwo);
	assert(*(size_t*)poppedElementOne == elementOne);
	assert(stack->Top == 0);
	assert(stack->IsEmpty == true);

	eskilib_stack_free(stack);
}

void eskilib_stack_tests()
{
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
