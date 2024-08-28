#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "eskilib_queue.h"
#include "eskilib_error_handler.h"

eskilib_Queue* eskilib_queue_allocate(const size_t sizeOfQueue, const size_t sizeOfElements)
{
	eskilib_Queue* queue = NULL;

	assert(sizeOfQueue != 0);
	assert(sizeOfElements != 0);
	if (sizeOfQueue == 0 || sizeOfElements == 0)
		return NULL;

	queue = malloc(sizeof(eskilib_Queue));

	if (queue == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Queue.\n");

	queue->Elements = malloc(sizeOfQueue * sizeOfElements);

	if (queue->Elements == NULL)
		eskilib_output_allocation_error_and_exit("Error allocating eskilib_Queue->Elements.\n");

	queue->First = 0;
	queue->Last = 0;
	queue->Size = sizeOfQueue;
	queue->IsEmpty = true;

	return queue;
}

void eskilib_queue_free(eskilib_Queue* queue)
{
	assert(queue != NULL);
	if (queue == NULL)
		return;

	free(queue->Elements);
	queue->Elements = NULL;

	free(queue);
	queue = NULL;
}

bool eskilib_queue_enqueue(void* element, eskilib_Queue* queue)
{
	assert(queue != NULL);
	if (queue == NULL)
		return false;

	assert(element != NULL);
	if (element == NULL)
		return false;

	if (queue->Last == INT64_MAX - 1)
		return false;

	if (queue->IsEmpty == true)
		queue->IsEmpty = false;
	else
		queue->Last++;

	queue->Elements[queue->Last] = element;

	return true;
}

void* eskilib_queue_dequeue(eskilib_Queue* queue)
{
	void* elementToDequeue = NULL;

	assert(queue != NULL);
	if (queue == NULL)
		return NULL;

	if (queue->IsEmpty == true || queue->First > queue->Last)
		return NULL;

	elementToDequeue = queue->Elements[queue->First];

	if (queue->First == queue->Last && queue->IsEmpty == false)
	{
		queue->IsEmpty = true;

		return elementToDequeue;
	}
	
	queue->First++;

	return elementToDequeue;
}
