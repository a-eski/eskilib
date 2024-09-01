#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "eskilib_test.h"
#include "eskilib_queue.h"

#define ESKILIB_TEST_QUEUE_SIZE 10

void eskilib_queue_allocate_test()
{
	eskilib_Queue* queue = NULL;

	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(size_t*));

	assert(queue != NULL);
	assert(queue->first == 0);
	assert(queue->last == 0);
	assert(queue->isEmpty == true);
	assert(queue->elements != NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_enqueue_empty_queue_test()
{
	eskilib_Queue* queue = NULL;
	size_t* value = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;

	value = malloc(sizeof(size_t));
	*value = 1001;

	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(value));

	enqueueResult = eskilib_queue_enqueue(value, queue);

	assert(enqueueResult == SUCCESS);
	assert(queue->first == 0);
	assert(queue->last == 0);
	assert(queue->isEmpty == false);
	assert(*(size_t*)queue->elements[0] == *value);

	free(value);
	eskilib_queue_free(queue);
}

void eskilib_queue_enqueue_nonempty_queue_test()
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResultOne = FAILURE;
	enum eskilib_Queue_Result enqueueResultTwo = FAILURE;
	size_t* valueOne = malloc(sizeof(size_t));
	size_t* valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);

	assert(enqueueResultOne == SUCCESS);
	assert(enqueueResultTwo == SUCCESS);
	assert(queue->first == 0);
	assert(queue->last == 1);
	assert(queue->isEmpty == false);
	assert(*(size_t*)queue->elements[0] == *valueOne);
	assert(*(size_t*)queue->elements[1] == *valueTwo);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_empty_queue_test()
{
	eskilib_Queue* queue = NULL;
	size_t* result = NULL;

	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(result));

	result = eskilib_queue_dequeue(queue);

	assert(queue->first == 0);
	assert(queue->last == 0);
	assert(queue->isEmpty == true);
	assert(result == NULL);

	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_nonempty_queue_to_empty_queue_test()
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResult = FAILURE;
	size_t* valueOne = NULL;
	size_t* result = NULL;
	
	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	*valueOne = 1001;

	enqueueResult = eskilib_queue_enqueue(valueOne, queue);

	result = eskilib_queue_dequeue(queue);

	assert(enqueueResult == SUCCESS);
	assert(queue->first == 0);
	assert(queue->last == 0);
	assert(queue->isEmpty == true);
	assert(*result == *valueOne);

	free(valueOne);
	eskilib_queue_free(queue);
}

void eskilib_queue_dequeue_nonempty_queue_test()
{
	eskilib_Queue* queue = NULL;
	enum eskilib_Queue_Result enqueueResultOne = false;
	enum eskilib_Queue_Result enqueueResultTwo = false;
	size_t* valueOne = NULL;
	size_t* valueTwo = NULL;
	size_t* result = NULL;
	
	queue = eskilib_queue_allocate(ESKILIB_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	enqueueResultOne = eskilib_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eskilib_queue_enqueue(valueTwo, queue);
	
	result = eskilib_queue_dequeue(queue);

	assert(enqueueResultOne == SUCCESS);
	assert(enqueueResultTwo == SUCCESS);
	assert(queue->first == 1);
	assert(queue->last == 1);
	assert(queue->isEmpty == false);
	assert(*result == *valueOne);

	free(valueOne);
	free(valueTwo);
	eskilib_queue_free(queue);
}

void eskilib_queue_release_tests()
{
}

void eskilib_queue_tests()
{
	#ifdef NDEBUG
		eskilib_queue_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_queue_allocate_test", eskilib_queue_allocate_test);

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
