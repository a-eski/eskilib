#include <stdio.h>
#include <stdlib.h>
#include "../etest.h"
#include "../eskilib_queue.h"

#define etest_QUEUE_SIZE 10

void eskilib_queue_malloc_test(void)
{
	eskilib_Queue* queue = NULL;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(size_t*));

	eassert(queue != NULL);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(queue->elements != NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_enqueue_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	size_t* value = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;

	value = malloc(sizeof(size_t));
	*value = 1001;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(value));

	enqueueResult = eskilib_queue_enqueue(value, queue);

	eassert(enqueueResult == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == false);
	eassert(*(size_t*)queue->elements[0] == *value);

	free(value);
	eskilib_queue_free(queue);
}

void eskilib_queue_enqueue_nonempty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResultOne = FAILURE;
	enum eskilib_Queue_Result enqueueResultTwo = FAILURE;
	size_t* valueOne = malloc(sizeof(size_t));
	size_t* valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);

	eassert(enqueueResultOne == SUCCESS);
	eassert(enqueueResultTwo == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 1);
	eassert(queue->isEmpty == false);
	eassert(*(size_t*)queue->elements[0] == *valueOne);
	eassert(*(size_t*)queue->elements[1] == *valueTwo);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	size_t* result = NULL;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(result));

	result = eskilib_queue_dequeue(queue);

	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(result == NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;
	size_t* valueOne = NULL;
	size_t* result = NULL;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	*valueOne = 1001;

	enqueueResult = eskilib_queue_enqueue(valueOne, queue);

	result = eskilib_queue_dequeue(queue);

	eassert(enqueueResult == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(*result == *valueOne);

	free(valueOne);
	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_nonempty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResultOne = false;
	enum eskilib_Queue_Result enqueueResultTwo = false;
	size_t* valueOne = NULL;
	size_t* valueTwo = NULL;
	size_t* result = NULL;

	queue = eskilib_queue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);

	result = eskilib_queue_dequeue(queue);

	eassert(enqueueResultOne == SUCCESS);
	eassert(enqueueResultTwo == SUCCESS);
	eassert(queue->first == 1);
	eassert(queue->last == 1);
	eassert(queue->isEmpty == false);
	eassert(*result == *valueOne);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_tests(void)
{
	etest_start();

	etest_run(eskilib_queue_malloc_test);
	etest_run(eskilib_queue_enqueue_empty_queue_test);
	etest_run(eskilib_queue_enqueue_nonempty_queue_test);
	etest_run(eskilib_queue_dequeue_empty_queue_test);
	etest_run(eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test);
	etest_run(eskilib_queue_dequeue_nonempty_queue_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	eskilib_queue_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
