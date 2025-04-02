/* Copyright (C) eskilib by Alex Eski 2024 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "eskilib_queue.h"
#include "eskilib_error_handler.h"

eskilib_Queue* eskilib_queue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements)
{
	eskilib_Queue* queue = NULL;

	assert(sizeOfQueue != 0);
	assert(sizeOfElements != 0);
	if (sizeOfQueue == 0 || sizeOfElements == 0)
		return NULL;

	queue = malloc(sizeof(eskilib_Queue));

	if (queue == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Queue.\n");

	queue->elements = malloc(sizeOfQueue * sizeOfElements);

	if (queue->elements == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Queue->elements.\n");

	queue->first = 0;
	queue->last = 0;
	queue->size = sizeOfQueue;
	queue->isEmpty = true;

	return queue;
}

void eskilib_queue_free(eskilib_Queue* queue)
{
	assert(queue != NULL);
	if (queue == NULL)
		return;

	free(queue->elements);
	queue->elements = NULL;

	free(queue);
	queue = NULL;
}

enum eskilib_Queue_Result eskilib_queue_enqueue(void* element, eskilib_Queue* queue)
{
	assert(queue != NULL);
	if (queue == NULL)
		return FAILURE_NULL_QUEUE;

	assert(element != NULL);
	if (element == NULL)
		return FAILURE_NULL_ELEMENT;

	if (queue->last == INT64_MAX - 1)
		return FAILURE_OVERFLOW_PROTECTION;

	if (queue->isEmpty == true)
		queue->isEmpty = false;
	else
		queue->last++;

	queue->elements[queue->last] = element;

	return SUCCESS;
}

void* eskilib_queue_dequeue(eskilib_Queue* queue)
{
	void* elementToDequeue = NULL;

	assert(queue != NULL);
	if (queue == NULL)
		return NULL;

	if (queue->isEmpty == true || queue->first > queue->last)
		return NULL;

	elementToDequeue = queue->elements[queue->first];

	if (queue->first == queue->last && queue->isEmpty == false)
	{
		queue->isEmpty = true;

		return elementToDequeue;
	}

	queue->first++;

	return elementToDequeue;
}
