/* Copyright (c) eskilib by Alex Eski 2024 */

#ifndef eskilib_stack_h
#define eskilib_stack_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum eskilib_Stack_Result
{
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_STACK = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct
{
	size_t top;
	size_t size;
	bool isEmpty;
	void** elements;
} eskilib_Stack;

eskilib_Stack* eskilib_stack_malloc(const size_t sizeOfStack, const size_t sizeOfElements);

void* eskilib_stack_pop(eskilib_Stack* stack);

enum eskilib_Stack_Result eskilib_stack_push(void* element, eskilib_Stack* stack);

void eskilib_stack_free(eskilib_Stack* stack);

#endif /* !eskilib_stack_h */
