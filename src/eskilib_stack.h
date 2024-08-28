#ifndef eskilib_stack_h
#define eskilib_stack_h

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	size_t Top;
	size_t Size;
	bool IsEmpty;
	void** Elements;
} eskilib_Stack;

eskilib_Stack* eskilib_stack_allocate(const size_t sizeOfStack, const size_t sizeOfElements);

void* eskilib_stack_pop(eskilib_Stack* stack);

bool eskilib_stack_push(void* element, eskilib_Stack* stack);

void eskilib_stack_free(eskilib_Stack* stack);

#endif /* !eskilib_stack_h */

