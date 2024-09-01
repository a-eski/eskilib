#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "eskilib_error_handler.h"
#include "eskilib_stack.h"

eskilib_Stack* eskilib_stack_allocate(const size_t sizeOfStack, const size_t sizeOfElements)
{
	eskilib_Stack* stack = NULL;
	
	assert(sizeOfStack != 0);
	assert(sizeOfElements != 0);
	if (sizeOfStack == 0 || sizeOfElements == 0)
		return NULL;

	stack = malloc(sizeof(eskilib_Stack));

	if (stack == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Stack.\n");

	stack->elements = malloc(sizeOfStack * sizeOfElements);

	if (stack->elements == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Stack->Elements.\n");

	stack->top = 0;
	stack->isEmpty = true;
	stack->size = sizeOfStack;

	return stack;
}

void* eskilib_stack_pop(eskilib_Stack* stack)
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

enum eskilib_Stack_Result eskilib_stack_push(void* element, eskilib_Stack* stack)
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

void eskilib_stack_free(eskilib_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return;

	free(stack->elements);
	stack->elements = NULL;

	free(stack);
	stack = NULL;
}
