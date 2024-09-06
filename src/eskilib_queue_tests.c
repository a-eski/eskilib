#include <stdio.h>
#include <stdlib.h>
#include "eskilib_test.h"
#include "eskilib_queue.h"

#define ESKILIB_TEST_QUEUE_SIZE 10

void eskilib_queue_malloc_test(void)
{
	eskilib_Queue* queue = NULL;

	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(size_t*));

	eskilib_assert(queue != NULL);
	eskilib_assert(queue->first == 0);
	eskilib_assert(queue->last == 0);
	eskilib_assert(queue->isEmpty == true);
	eskilib_assert(queue->elements != NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_enqueue_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	size_t* value = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;

	value = malloc(sizeof(size_t));
	*value = 1001;

	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(value));

	enqueueResult = eskilib_queue_enqueue(value, queue);

	eskilib_assert(enqueueResult == SUCCESS);
	eskilib_assert(queue->first == 0);
	eskilib_assert(queue->last == 0);
	eskilib_assert(queue->isEmpty == false);
	eskilib_assert(*(size_t*)queue->elements[0] == *value);

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

	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);

	eskilib_assert(enqueueResultOne == SUCCESS);
	eskilib_assert(enqueueResultTwo == SUCCESS);
	eskilib_assert(queue->first == 0);
	eskilib_assert(queue->last == 1);
	eskilib_assert(queue->isEmpty == false);
	eskilib_assert(*(size_t*)queue->elements[0] == *valueOne);
	eskilib_assert(*(size_t*)queue->elements[1] == *valueTwo);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	size_t* result = NULL;

	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(result));

	result = eskilib_queue_dequeue(queue);

	eskilib_assert(queue->first == 0);
	eskilib_assert(queue->last == 0);
	eskilib_assert(queue->isEmpty == true);
	eskilib_assert(result == NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test(void)
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;
	size_t* valueOne = NULL;
	size_t* result = NULL;
	
	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	*valueOne = 1001;

	enqueueResult = eskilib_queue_enqueue(valueOne, queue);

	result = eskilib_queue_dequeue(queue);

	eskilib_assert(enqueueResult == SUCCESS);
	eskilib_assert(queue->first == 0);
	eskilib_assert(queue->last == 0);
	eskilib_assert(queue->isEmpty == true);
	eskilib_assert(*result == *valueOne);

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
	
	queue = eskilib_queue_malloc(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);
	
	result = eskilib_queue_dequeue(queue);

	eskilib_assert(enqueueResultOne == SUCCESS);
	eskilib_assert(enqueueResultTwo == SUCCESS);
	eskilib_assert(queue->first == 1);
	eskilib_assert(queue->last == 1);
	eskilib_assert(queue->isEmpty == false);
	eskilib_assert(*result == *valueOne);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_release_tests(void)
{
}

void eskilib_queue_tests(void)
{
	#ifdef NDEBUG
		eskilib_queue_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_queue_malloc_test", eskilib_queue_malloc_test);

	eskilib_test_run("eskilib_queue_enqueue_empty_queue_test", eskilib_queue_enqueue_empty_queue_test);

	eskilib_test_run("eskilib_queue_enqueue_nonempty_queue_test", eskilib_queue_enqueue_nonempty_queue_test);

	eskilib_test_run("eskilib_queue_dequeue_empty_queue_test", eskilib_queue_dequeue_empty_queue_test);

	eskilib_test_run("eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test", eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test);

	eskilib_test_run("eskilib_queue_dequeue_nonempty_queue_test", eskilib_queue_dequeue_nonempty_queue_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_queue_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
