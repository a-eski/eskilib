/* Copyright (C) eskilib by Alex Eski 2024 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "estack.h"

estack* estack_malloc(const size_t sizeOfStack, const size_t sizeOfElements)
{
	estack* stack = NULL;

	assert(sizeOfStack != 0);
	assert(sizeOfElements != 0);
	if (sizeOfStack == 0 || sizeOfElements == 0)
		return NULL;

	stack = malloc(sizeof(estack));

	if (stack == NULL) {
		return NULL;
	}

	stack->elements = malloc(sizeOfStack * sizeOfElements);

	if (stack->elements == NULL) {
		return NULL;
	}

	stack->top = 0;
	stack->isEmpty = true;
	stack->size = sizeOfStack;

	return stack;
}

void* estack_pop(estack* stack)
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

enum estack_Result estack_push(void* element, estack* stack)
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

void estack_free(estack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return;

	free(stack->elements);
	stack->elements = NULL;

	free(stack);
	stack = NULL;
}
