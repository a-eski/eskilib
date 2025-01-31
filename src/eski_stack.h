#ifndef eski_stack_h
#define eski_stack_h

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum eski_Stack_Result
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
} eski_Stack;

eski_Stack* eski_stack_malloc(const size_t sizeOfStack, const size_t sizeOfElements);

void* eski_stack_pop(eski_Stack* stack);

enum eski_Stack_Result eski_stack_push(void* element, eski_Stack* stack);

void eski_stack_free(eski_Stack* stack);

#endif /* !eski_stack_h */
