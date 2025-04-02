/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef eskilib_queue_h
#define eskilib_queue_h

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum eskilib_Queue_Result
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
} eskilib_Queue;

eskilib_Queue* eskilib_queue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements);

void eskilib_queue_free(eskilib_Queue* queue);

enum eskilib_Queue_Result eskilib_queue_enqueue(void* element, eskilib_Queue* queue);

void* eskilib_queue_dequeue(eskilib_Queue* queue);

#endif /* !eskilib_queue_h */
