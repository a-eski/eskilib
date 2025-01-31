#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "eski_error_handler.h"
#include "eski_stack.h"

eski_Stack* eski_stack_malloc(const size_t sizeOfStack, const size_t sizeOfElements)
{
	eski_Stack* stack = NULL;

	assert(sizeOfStack != 0);
	assert(sizeOfElements != 0);
	if (sizeOfStack == 0 || sizeOfElements == 0)
		return NULL;

	stack = malloc(sizeof(eski_Stack));

	if (stack == NULL)
		eski_output_allocation_error_and_exit("Error allocating eski_Stack.\n");

	stack->elements = malloc(sizeOfStack * sizeOfElements);

	if (stack->elements == NULL)
		eski_output_allocation_error_and_exit("Error allocating eski_Stack->Elements.\n");

	stack->top = 0;
	stack->isEmpty = true;
	stack->size = sizeOfStack;

	return stack;
}

void* eski_stack_pop(eski_Stack* stack)
{
	void* elementToPop = NULL;

	assert(stack != NULL);
        if (stack == NULL || stack->isEmpty == true)
        	return NULL;

        elementToPop = stack->elements[stack->top];
	if (stack->top >= 1)
		stack->top = stack->top - 1;
	else
		stack->isEmpty = true;

	return elementToPop;
}

enum eski_Stack_Result eski_stack_push(void* element, eski_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return FAILURE_NULL_STACK;

	assert(element != NULL);
	if (element == NULL)
		return FAILURE_NULL_ELEMENT;

	if (stack->top >= SIZE_MAX - 1 || stack->top > stack->size)
		return FAILURE_OVERFLOW_PROTECTION;

	if (stack->top == 0 && stack->isEmpty == true)
		stack->isEmpty = false;
	else
		stack->top = stack->top + 1;

	stack->elements[stack->top] = element;

	return SUCCESS;
}

void eski_stack_free(eski_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return;

	free(stack->elements);
	stack->elements = NULL;

	free(stack);
	stack = NULL;
}
