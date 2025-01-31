#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "eski_queue.h"
#include "eski_error_handler.h"

eski_Queue* eski_queue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements)
{
	eski_Queue* queue = NULL;

	assert(sizeOfQueue != 0);
	assert(sizeOfElements != 0);
	if (sizeOfQueue == 0 || sizeOfElements == 0)
		return NULL;

	queue = malloc(sizeof(eski_Queue));

	if (queue == NULL)
		eski_output_allocation_error_and_exit("Error allocating eski_Queue.\n");

	queue->elements = malloc(sizeOfQueue * sizeOfElements);

	if (queue->elements == NULL)
		eski_output_allocation_error_and_exit("Error allocating eski_Queue->elements.\n");

	queue->first = 0;
	queue->last = 0;
	queue->size = sizeOfQueue;
	queue->isEmpty = true;

	return queue;
}

void eski_queue_free(eski_Queue* queue)
{
	assert(queue != NULL);
	if (queue == NULL)
		return;

	free(queue->elements);
	queue->elements = NULL;

	free(queue);
	queue = NULL;
}

enum eski_Queue_Result eski_queue_enqueue(void* element, eski_Queue* queue)
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

void* eski_queue_dequeue(eski_Queue* queue)
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
