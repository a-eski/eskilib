/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ESKILIB_EQUEUE_H_
#define ESKILIB_EQUEUE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum equeue_Result
{
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ELEMENT = -2,
	FAILURE_NULL_QUEUE = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct
{
	size_t first;
	size_t last;
	size_t size;
	bool isEmpty;
	void** elements;
} equeue;

equeue* equeue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements);

void equeue_free(equeue* queue);

enum equeue_Result equeue_enqueue(void* element, equeue* queue);

void* equeue_dequeue(equeue* queue);

#ifdef __cplusplus
}
#endif

#endif /* !ESKILIB_EQUEUE_H_ */
