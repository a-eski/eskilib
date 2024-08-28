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

	stack->Elements = malloc(sizeOfStack * sizeOfElements);

	if (stack->Elements == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Stack->Elements.\n");

	stack->Top = 0;
	stack->IsEmpty = true;
	stack->Size = sizeOfStack;

	return stack;
}

void* eskilib_stack_pop(eskilib_Stack* stack)
{
	void* elementToPop = NULL;	

	assert(stack != NULL);
        if (stack == NULL || stack->IsEmpty == true)
        	return NULL;

        elementToPop = stack->Elements[stack->Top];
	if (stack->Top >= 1)
		stack->Top = stack->Top - 1;
	else
		stack->IsEmpty = true;	

	return elementToPop;
}

bool eskilib_stack_push(void* element, eskilib_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return false;

	assert(element != NULL);
	if (element == NULL)
		return false;

	if (stack->Top >= SIZE_MAX - 1 || stack->Top > stack->Size)
		return false;

	if (stack->Top == 0 && stack->IsEmpty == true)
		stack->IsEmpty = false;
	else
		stack->Top = stack->Top + 1;

	stack->Elements[stack->Top] = element;

	return true;
}

void eskilib_stack_free(eskilib_Stack* stack)
{
	assert(stack != NULL);
	if (stack == NULL)
		return;

	free(stack->Elements);
	stack->Elements = NULL;

	free(stack);
	stack = NULL;
}
