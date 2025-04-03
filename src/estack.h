/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_ESTACK_H_
#define ESKILIB_ESTACK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

enum estack_Result
{
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_STACK = -1,
	FAILURE = 0,
	SUCCESS = 1
};

struct estack
{
	size_t top;
	size_t size;
	bool isEmpty;
	void** elements;
};
typedef struct estack estack;

estack* estack_malloc(const size_t sizeOfStack, const size_t sizeOfElements);

void* estack_pop(estack* stack);

enum estack_Result estack_push(void* element, estack* stack);

void estack_free(estack* stack);

#ifdef __cplusplus
}
#endif

#endif /* !ESKILIB_ESTACK_H_ */
