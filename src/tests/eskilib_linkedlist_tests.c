#include <stdio.h>
#include <stdlib.h>
#include "../etest.h"
#include "../eskilib_linkedlist.h"

void eskilib_linkedlist_malloc_test(void)
{
	eskilib_LinkedList* linkedList = NULL;

	linkedList = eskilib_linkedlist_malloc();

	eassert(linkedList != NULL);
	eassert(linkedList->first == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_linkednode_malloc_test(void)
{
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	node = eskilib_linkedlist_linkednode_malloc(&value);

	eassert(node != NULL);
	eassert(value == *(size_t*)node->value);
	eassert(node->next == NULL);

	free(node);
}

void eskilib_linkedlist_set_first_on_empty_linkedlist_test(void)
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eskilib_LinkedList_Result setFirstResult = FAILURE;

	linkedList = eskilib_linkedlist_malloc();
	node = eskilib_linkedlist_linkednode_malloc(&value);

	setFirstResult = eskilib_linkedlist_set_first(node, linkedList);

	eassert(setFirstResult == SUCCESS);
	eassert(linkedList->first == node);
	eassert(linkedList->first->value == node->value);
	eassert(linkedList->first->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_first_on_nonempty_linkedlist_test(void)
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eskilib_LinkedList_Result setFirstResultOne = FAILURE;
	enum eskilib_LinkedList_Result setFirstResultTwo = FAILURE;

	linkedList = eskilib_linkedlist_malloc();
	node = eskilib_linkedlist_linkednode_malloc(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_malloc(&valueTwo);

	setFirstResultOne = eskilib_linkedlist_set_first(node, linkedList);
	setFirstResultTwo = eskilib_linkedlist_set_first(nextNode, linkedList);

	eassert(setFirstResultOne == SUCCESS);
	eassert(setFirstResultTwo == SUCCESS);
	eassert(linkedList->first == nextNode);
	eassert(linkedList->first->value == nextNode->value);
	eassert(linkedList->first->next == node);
	eassert(linkedList->first->next->value == node->value);
	eassert(linkedList->first->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_empty_linkedlist_test(void)
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eskilib_LinkedList_Result setLastResult = FAILURE;

	linkedList = eskilib_linkedlist_malloc();
	node = eskilib_linkedlist_linkednode_malloc(&value);

	setLastResult = eskilib_linkedlist_set_last(node, linkedList);

	eassert(setLastResult == SUCCESS);
	eassert(value == *(size_t*)linkedList->first->value);
	eassert(linkedList->first->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_nonempty_linkedlist_test(void)
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eskilib_LinkedList_Result setLastResultOne = FAILURE;
	enum eskilib_LinkedList_Result setLastResultTwo = FAILURE;

	linkedList = eskilib_linkedlist_malloc();
	node = eskilib_linkedlist_linkednode_malloc(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_malloc(&valueTwo);

	setLastResultOne = eskilib_linkedlist_set_last(node, linkedList);
	setLastResultTwo = eskilib_linkedlist_set_last(nextNode, linkedList);

	eassert(setLastResultOne == SUCCESS);
	eassert(setLastResultTwo == SUCCESS);
	eassert(linkedList->first == node);
	eassert(valueOne == *(size_t*)linkedList->first->value);
	eassert(linkedList->first->next == nextNode);
	eassert(valueTwo == *(size_t*)linkedList->first->next->value);
	eassert(linkedList->first->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_after_test(void)
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* secondNode = NULL;
	eskilib_LinkedList_LinkedNode* thirdNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;
	enum eskilib_LinkedList_Result setFirstResult = FAILURE;
	enum eskilib_LinkedList_Result setLastResult = FAILURE;
	enum eskilib_LinkedList_Result setAfterResult = FAILURE;

	linkedList = eskilib_linkedlist_malloc();
	node = eskilib_linkedlist_linkednode_malloc(&valueOne);
	secondNode = eskilib_linkedlist_linkednode_malloc(&valueTwo);
	thirdNode = eskilib_linkedlist_linkednode_malloc(&valueThree);

	setFirstResult = eskilib_linkedlist_set_first(node, linkedList);
	setLastResult = eskilib_linkedlist_set_last(secondNode, linkedList);

	setAfterResult = eskilib_linkedlist_set_after(linkedList->first, thirdNode);

	eassert(setFirstResult == SUCCESS);
	eassert(setLastResult == SUCCESS);
	eassert(setAfterResult == SUCCESS);
	eassert(linkedList->first == node);
	eassert(valueOne == *(size_t*)linkedList->first->value);
	eassert(linkedList->first->next == thirdNode);
	eassert(valueThree == *(size_t*)linkedList->first->next->value);
	eassert(linkedList->first->next->next == secondNode);
	eassert(linkedList->first->next->next->value);
	eassert(linkedList->first->next->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_release_tests(void)
{
}

void eskilib_linkedlist_tests(void)
{
	etest_start();

	etest_run(eskilib_linkedlist_malloc_test);
	etest_run(eskilib_linkedlist_linkednode_malloc_test);
	etest_run(eskilib_linkedlist_set_first_on_empty_linkedlist_test);
	etest_run(eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);
	etest_run(eskilib_linkedlist_set_last_on_empty_linkedlist_test);
	etest_run(eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);
	etest_run(eskilib_linkedlist_set_after_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	eskilib_linkedlist_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
