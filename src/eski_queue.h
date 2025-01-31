#ifndef eski_queue_h
#define eski_queue_h

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

enum eski_Queue_Result
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
} eski_Queue;

eski_Queue* eski_queue_malloc(const size_t sizeOfQueue, const size_t sizeOfElements);

void eski_queue_free(eski_Queue* queue);

enum eski_Queue_Result eski_queue_enqueue(void* element, eski_Queue* queue);

void* eski_queue_dequeue(eski_Queue* queue);

#endif /* !eski_queue_h */
