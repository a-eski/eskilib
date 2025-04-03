#include <stdio.h>
#include <stdlib.h>
#include "../etest.h"
#include "../equeue.h"

#define etest_QUEUE_SIZE 10

void equeue_malloc_test(void)
{
	equeue* queue = NULL;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(size_t*));

	eassert(queue != NULL);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(queue->elements != NULL);

	equeue_free(queue);
}

void equeue_enqueue_empty_queue_test(void)
{
	equeue* queue = NULL;
	size_t* value = NULL;
	enum equeue_Result enqueueResult = FAILURE;

	value = malloc(sizeof(size_t));
	*value = 1001;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(value));

	enqueueResult = equeue_enqueue(value, queue);

	eassert(enqueueResult == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == false);
	eassert(*(size_t*)queue->elements[0] == *value);

	free(value);
	equeue_free(queue);
}

void equeue_enqueue_nonempty_queue_test(void)
{
	equeue* queue = NULL;
	enum equeue_Result enqueueResultOne = FAILURE;
	enum equeue_Result enqueueResultTwo = FAILURE;
	size_t* valueOne = malloc(sizeof(size_t));
	size_t* valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	enqueueResultOne = equeue_enqueue(valueOne, queue);
	enqueueResultTwo = equeue_enqueue(valueTwo, queue);

	eassert(enqueueResultOne == SUCCESS);
	eassert(enqueueResultTwo == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 1);
	eassert(queue->isEmpty == false);
	eassert(*(size_t*)queue->elements[0] == *valueOne);
	eassert(*(size_t*)queue->elements[1] == *valueTwo);

	free(valueOne);
	free(valueTwo);
	equeue_free(queue);
}

void equeue_dequeue_empty_queue_test(void)
{
	equeue* queue = NULL;
	size_t* result = NULL;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(result));

	result = equeue_dequeue(queue);

	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(result == NULL);

	equeue_free(queue);
}

void equeue_dequeue_nonempty_queue_to_empty_queue_test(void)
{
	equeue* queue = NULL;
	enum equeue_Result enqueueResult = FAILURE;
	size_t* valueOne = NULL;
	size_t* result = NULL;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	*valueOne = 1001;

	enqueueResult = equeue_enqueue(valueOne, queue);

	result = equeue_dequeue(queue);

	eassert(enqueueResult == SUCCESS);
	eassert(queue->first == 0);
	eassert(queue->last == 0);
	eassert(queue->isEmpty == true);
	eassert(*result == *valueOne);

	free(valueOne);
	equeue_free(queue);
}

void equeue_dequeue_nonempty_queue_test(void)
{
	equeue* queue = NULL;
	enum equeue_Result enqueueResultOne = false;
	enum equeue_Result enqueueResultTwo = false;
	size_t* valueOne = NULL;
	size_t* valueTwo = NULL;
	size_t* result = NULL;

	queue = equeue_malloc(etest_QUEUE_SIZE, sizeof(valueOne));

	valueOne = malloc(sizeof(size_t));
	valueTwo = malloc(sizeof(size_t));
	*valueOne = 1001;
	*valueTwo = 2002;

	enqueueResultOne = equeue_enqueue(valueOne, queue);
	enqueueResultTwo = equeue_enqueue(valueTwo, queue);

	result = equeue_dequeue(queue);

	eassert(enqueueResultOne == SUCCESS);
	eassert(enqueueResultTwo == SUCCESS);
	eassert(queue->first == 1);
	eassert(queue->last == 1);
	eassert(queue->isEmpty == false);
	eassert(*result == *valueOne);

	free(valueOne);
	free(valueTwo);
	equeue_free(queue);
}

void equeue_tests(void)
{
	etest_start();

	etest_run(equeue_malloc_test);
	etest_run(equeue_enqueue_empty_queue_test);
	etest_run(equeue_enqueue_nonempty_queue_test);
	etest_run(equeue_dequeue_empty_queue_test);
	etest_run(equeue_dequeue_nonempty_queue_to_empty_queue_test);
	etest_run(equeue_dequeue_nonempty_queue_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	equeue_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
