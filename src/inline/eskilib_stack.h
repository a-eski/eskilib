#ifndef eskilib_stack_h
#define eskilib_stack_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"

enum eskilib_Stack_Result
{
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_STACK = -1,
	FAILURE = 0,
	SUCCESS = 1
};

#endif /* !eskilib_stack_h */

#ifndef eskilib_Stack_TYPE
#error "eskilib_Stack_TYPE must be defined";
#endif // !eskilib_Stack_TYPE

typedef struct eskilib_Stack eskilib_Stack;
struct eskilib_Stack
{
	size_t top;
	size_t size;
	bool isEmpty;
	eskilib_Stack_TYPE* elements;
};

static inline eskilib_Stack* eskilib_stack_malloc(const size_t sizeOfStack)
{
	eskilib_Stack* stack = NULL;
	
	assert(sizeOfStack != 0);
	if (sizeOfStack == 0)
		return NULL;

	stack = malloc(sizeof(eskilib_Stack));

	if (stack == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Stack.\n");

	stack->elements = malloc(sizeOfStack * sizeof(eskilib_Stack_TYPE));

	if (stack->elements == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Stack->Elements.\n");

	stack->top = 0;
	stack->isEmpty = true;
	stack->size = sizeOfStack;

	return stack;
}

static inline eskilib_Stack_TYPE eskilib_stack_pop(eskilib_Stack* stack)
{
	eskilib_Stack_TYPE elementToPop;

	assert(stack != NULL);
        if (stack == NULL || stack->isEmpty == true)
        	return (eskilib_Stack_TYPE)NULL;

        elementToPop = stack->elements[stack->top];
	if (stack->top >= 1)
		stack->top = stack->top - 1;
	else
		stack->isEmpty = true;	

	return elementToPop;
}

static inline enum eskilib_Stack_Result eskilib_stack_push(eskilib_Stack_TYPE element, eskilib_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return FAILURE_NULL_STACK;

	if (stack->top >= SIZE_MAX - 1 || stack->top > stack->size)
		return FAILURE_OVERFLOW_PROTECTION;

	if (stack->top == 0 && stack->isEmpty == true)
		stack->isEmpty = false;
	else
		stack->top = stack->top + 1;

	stack->elements[stack->top] = element;

	return SUCCESS;
}

static inline void eskilib_stack_free(eskilib_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return;

	free(stack->elements);
	stack->elements = NULL;

	free(stack);
	stack = NULL;
}

#undef eskilib_Stack_TYPE

