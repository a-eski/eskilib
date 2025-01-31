#include <stdio.h>
#include <stdlib.h>
#include "../eski_test.h"
#include "../eski_queue.h"

#define eski_TEST_QUEUE_SIZE 10

void eski_queue_malloc_test(void)
{
	eski_Queue* queue = NULL;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(size_t*));

	eski_assert(queue != NULL);
	eski_assert(queue->first == 0);
	eski_assert(queue->last == 0);
	eski_assert(queue->isEmpty == true);
	eski_assert(queue->elements != NULL);

	eski_queue_free(queue);
}

void eski_queue_enqueue_empty_queue_test(void)
{
	eski_Queue* queue = NULL;
	size_t* value = NULL;
	enum eski_Queue_Result enqueueResult = FAILURE;

	value = malloc(sizeof(size_t));
	*value = 1001;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(value));

	enqueueResult = eski_queue_enqueue(value, queue);

	eski_assert(enqueueResult == SUCCESS);
	eski_assert(queue->first == 0);
	eski_assert(queue->last == 0);
	eski_assert(queue->isEmpty == false);
	eski_assert(*(size_t*)queue->elements[0] == *value);

	free(value);
	eski_queue_free(queue);
}

void eski_queue_enqueue_nonempty_queue_test(void)
{
	eski_Queue* queue = NULL;
	enum eski_Queue_Result enqueueResultOne = FAILURE;
	enum eski_Queue_Result enqueueResultTwo = FAILURE;
	size_t* valueOne = malloc(sizeof(size_t));
	size_t* valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(valueOne));

	enqueueResultOne = eski_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eski_queue_enqueue(valueTwo, queue);

	eski_assert(enqueueResultOne == SUCCESS);
	eski_assert(enqueueResultTwo == SUCCESS);
	eski_assert(queue->first == 0);
	eski_assert(queue->last == 1);
	eski_assert(queue->isEmpty == false);
	eski_assert(*(size_t*)queue->elements[0] == *valueOne);
	eski_assert(*(size_t*)queue->elements[1] == *valueTwo);

	free(valueOne);
	free(valueTwo);
	eski_queue_free(queue);
}

void eski_queue_dequeue_empty_queue_test(void)
{
	eski_Queue* queue = NULL;
	size_t* result = NULL;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(result));

	result = eski_queue_dequeue(queue);

	eski_assert(queue->first == 0);
	eski_assert(queue->last == 0);
	eski_assert(queue->isEmpty == true);
	eski_assert(result == NULL);

	eski_queue_free(queue);
}

void eski_queue_dequeue_nonempty_queue_to_empty_queue_test(void)
{
	eski_Queue* queue = NULL;
	enum eski_Queue_Result enqueueResult = FAILURE;
	size_t* valueOne = NULL;
	size_t* result = NULL;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	*valueOne = 1001;

	enqueueResult = eski_queue_enqueue(valueOne, queue);

	result = eski_queue_dequeue(queue);

	eski_assert(enqueueResult == SUCCESS);
	eski_assert(queue->first == 0);
	eski_assert(queue->last == 0);
	eski_assert(queue->isEmpty == true);
	eski_assert(*result == *valueOne);

	free(valueOne);
	eski_queue_free(queue);
}

void eski_queue_dequeue_nonempty_queue_test(void)
{
	eski_Queue* queue = NULL;
	enum eski_Queue_Result enqueueResultOne = false;
	enum eski_Queue_Result enqueueResultTwo = false;
	size_t* valueOne = NULL;
	size_t* valueTwo = NULL;
	size_t* result = NULL;

	queue = eski_queue_malloc(eski_TEST_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	enqueueResultOne = eski_queue_enqueue(valueOne, queue);
	enqueueResultTwo = eski_queue_enqueue(valueTwo, queue);

	result = eski_queue_dequeue(queue);

	eski_assert(enqueueResultOne == SUCCESS);
	eski_assert(enqueueResultTwo == SUCCESS);
	eski_assert(queue->first == 1);
	eski_assert(queue->last == 1);
	eski_assert(queue->isEmpty == false);
	eski_assert(*result == *valueOne);

	free(valueOne);
	free(valueTwo);
	eski_queue_free(queue);
}

void eski_queue_release_tests(void)
{
}

void eski_queue_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_queue_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_queue_malloc_test", eski_queue_malloc_test);

	eski_test_run("eski_queue_enqueue_empty_queue_test", eski_queue_enqueue_empty_queue_test);

	eski_test_run("eski_queue_enqueue_nonempty_queue_test", eski_queue_enqueue_nonempty_queue_test);

	eski_test_run("eski_queue_dequeue_empty_queue_test", eski_queue_dequeue_empty_queue_test);

	eski_test_run("eski_queue_dequeue_nonempty_queue_to_empty_queue_test", eski_queue_dequeue_nonempty_queue_to_empty_queue_test);

	eski_test_run("eski_queue_dequeue_nonempty_queue_test", eski_queue_dequeue_nonempty_queue_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_queue_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
