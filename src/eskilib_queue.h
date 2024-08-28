#ifndef eskilib_queue_h
#define eskilib_queue_h

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
	size_t First;
	size_t Last;
	size_t Size;
	bool IsEmpty;
	void** Elements;
} eskilib_Queue;

eskilib_Queue* eskilib_queue_allocate(const size_t sizeOfQueue, const size_t sizeOfElements);

void eskilib_queue_free(eskilib_Queue* queue);

bool eskilib_queue_enqueue(void* element, eskilib_Queue* queue);

void* eskilib_queue_dequeue(eskilib_Queue* queue);

#endif /* !eskilib_queue_h */

