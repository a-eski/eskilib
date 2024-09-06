#include <stdio.h>
#include <stdlib.h>
#include "eskilib_test.h"
#include "eskilib_linkedlist.h"

void eskilib_linkedlist_malloc_test(void)
{
	eskilib_LinkedList* linkedList = NULL;

	linkedList = eskilib_linkedlist_malloc();

	eskilib_assert(linkedList != NULL);
	eskilib_assert(linkedList->first == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_linkednode_malloc_test(void)
{
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	node = eskilib_linkedlist_linkednode_malloc(&value);

	eskilib_assert(node != NULL);
	eskilib_assert(value == *(size_t*)node->value);
	eskilib_assert(node->next == NULL);

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

	eskilib_assert(setFirstResult == SUCCESS);
	eskilib_assert(linkedList->first == node);
	eskilib_assert(linkedList->first->value == node->value);
	eskilib_assert(linkedList->first->next == NULL);
	
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

	eskilib_assert(setFirstResultOne == SUCCESS);
	eskilib_assert(setFirstResultTwo == SUCCESS);
	eskilib_assert(linkedList->first == nextNode);
	eskilib_assert(linkedList->first->value == nextNode->value);
	eskilib_assert(linkedList->first->next == node);
	eskilib_assert(linkedList->first->next->value == node->value);
	eskilib_assert(linkedList->first->next->next == NULL);

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

	eskilib_assert(setLastResult == SUCCESS);
	eskilib_assert(value == *(size_t*)linkedList->first->value);
	eskilib_assert(linkedList->first->next == NULL);

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

	eskilib_assert(setLastResultOne == SUCCESS);
	eskilib_assert(setLastResultTwo == SUCCESS);
	eskilib_assert(linkedList->first == node);
	eskilib_assert(valueOne == *(size_t*)linkedList->first->value);
	eskilib_assert(linkedList->first->next == nextNode);
	eskilib_assert(valueTwo == *(size_t*)linkedList->first->next->value);
	eskilib_assert(linkedList->first->next->next == NULL);

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

	eskilib_assert(setFirstResult == SUCCESS);
	eskilib_assert(setLastResult == SUCCESS);
	eskilib_assert(setAfterResult == SUCCESS);
	eskilib_assert(linkedList->first == node);
	eskilib_assert(valueOne == *(size_t*)linkedList->first->value);
	eskilib_assert(linkedList->first->next == thirdNode);
	eskilib_assert(valueThree == *(size_t*)linkedList->first->next->value);
	eskilib_assert(linkedList->first->next->next == secondNode);
	eskilib_assert(linkedList->first->next->next->value);
	eskilib_assert(linkedList->first->next->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_release_tests(void)
{
}

void eskilib_linkedlist_tests(void)
{
	#ifdef NDEBUG
		eskilib_linkedlist_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_linkedlist_malloc_test", eskilib_linkedlist_malloc_test);

	eskilib_test_run("eskilib_linkedlist_linkednode_malloc_test", eskilib_linkedlist_linkednode_malloc_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_empty_linkedlist_test", eskilib_linkedlist_set_first_on_empty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_nonempty_linkedlist_test", eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_last_on_empty_linkedlist_test", eskilib_linkedlist_set_last_on_empty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_nonempty_linkedlist_test", eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_after_test", eskilib_linkedlist_set_after_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_linkedlist_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
