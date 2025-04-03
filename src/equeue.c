/* Copyright (C) eskilib by Alex Eski 2024 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "equeue.h"

equeue* equeue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements)
{
	equeue* queue = NULL;

	assert(sizeOfQueue != 0);
	assert(sizeOfElements != 0);
	if (sizeOfQueue == 0 || sizeOfElements == 0)
		return NULL;

	queue = malloc(sizeof(equeue));

	if (!queue) {
		return NULL;
	}

	queue->elements = malloc(sizeOfQueue * sizeOfElements);

	if (!queue->elements) {
		return NULL;
	}

	queue->first = 0;
	queue->last = 0;
	queue->size = sizeOfQueue;
	queue->isEmpty = true;

	return queue;
}

void equeue_free(equeue* queue)
{
	assert(queue);
	if (!queue) {
		return;
	}

	if (queue->elements) {
		free(queue->elements);
		queue->elements = NULL;
	}

	free(queue);
	queue = NULL;
}

enum equeue_Result equeue_enqueue(void* element, equeue* queue)
{
	assert(queue);
	if (!queue) {
		return FAILURE_NULL_QUEUE;
	}

	assert(element);
	if (!element) {
		return FAILURE_NULL_ELEMENT;
	}

	if (queue->last == INT64_MAX - 1)
		return FAILURE_OVERFLOW_PROTECTION;

	if (queue->isEmpty == true) {
		queue->isEmpty = false;
	}
	else {
		queue->last++;
	}

	queue->elements[queue->last] = element;

	return SUCCESS;
}

void* equeue_dequeue(equeue* queue)
{
	void* elementToDequeue = NULL;

	assert(queue);
	if (!queue) {
		return NULL;
	}

	if (queue->isEmpty == true || queue->first > queue->last) {
		return NULL;
	}

	elementToDequeue = queue->elements[queue->first];

	if (queue->first == queue->last && queue->isEmpty == false) {
		queue->isEmpty = true;

		return elementToDequeue;
	}

	queue->first++;

	return elementToDequeue;
}
