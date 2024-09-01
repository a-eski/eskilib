#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eskilib_test.h"
#include "eskilib_linkedlist.h"

void eskilib_linkedlist_allocate_test()
{
	eskilib_LinkedList* linkedList = NULL;

	linkedList = eskilib_linkedlist_allocate();

	assert(linkedList != NULL);
	assert(linkedList->first == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_linkednode_allocate_test()
{
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	node = eskilib_linkedlist_linkednode_allocate(&value);

	assert(node != NULL);
	assert(value == *(size_t*)node->value);
	assert(node->next == NULL);

	free(node);
}

void eskilib_linkedlist_set_first_on_empty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eskilib_LinkedList_Result setFirstResult = FAILURE;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&value);

	setFirstResult = eskilib_linkedlist_set_first(node, linkedList);

	assert(setFirstResult == SUCCESS);
	assert(linkedList->first == node);
	assert(linkedList->first->value == node->value);
	assert(linkedList->first->next == NULL);
	
	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_first_on_nonempty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eskilib_LinkedList_Result setFirstResultOne = FAILURE;
	enum eskilib_LinkedList_Result setFirstResultTwo = FAILURE;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);

	setFirstResultOne = eskilib_linkedlist_set_first(node, linkedList);
	setFirstResultTwo = eskilib_linkedlist_set_first(nextNode, linkedList);

	assert(setFirstResultOne == SUCCESS);
	assert(setFirstResultTwo == SUCCESS);
	assert(linkedList->first == nextNode);
	assert(linkedList->first->value == nextNode->value);
	assert(linkedList->first->next == node);
	assert(linkedList->first->next->value == node->value);
	assert(linkedList->first->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_empty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eskilib_LinkedList_Result setLastResult = FAILURE;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&value);

	setLastResult = eskilib_linkedlist_set_last(node, linkedList);

	assert(setLastResult == SUCCESS);
	assert(value == *(size_t*)linkedList->first->value);
	assert(linkedList->first->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_nonempty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eskilib_LinkedList_Result setLastResultOne = FAILURE;
	enum eskilib_LinkedList_Result setLastResultTwo = FAILURE;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);

	setLastResultOne = eskilib_linkedlist_set_last(node, linkedList);
	setLastResultTwo = eskilib_linkedlist_set_last(nextNode, linkedList);

	assert(setLastResultOne == SUCCESS);
	assert(setLastResultTwo == SUCCESS);
	assert(linkedList->first == node);
	assert(valueOne == *(size_t*)linkedList->first->value);
	assert(linkedList->first->next == nextNode);
	assert(valueTwo == *(size_t*)linkedList->first->next->value);
	assert(linkedList->first->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_after_test()
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

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	secondNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);
	thirdNode = eskilib_linkedlist_linkednode_allocate(&valueThree);

	setFirstResult = eskilib_linkedlist_set_first(node, linkedList);
	setLastResult = eskilib_linkedlist_set_last(secondNode, linkedList);

	setAfterResult = eskilib_linkedlist_set_after(linkedList->first, thirdNode);

	assert(setFirstResult == SUCCESS);
	assert(setLastResult == SUCCESS);
	assert(setAfterResult == SUCCESS);
	assert(linkedList->first == node);
	assert(valueOne == *(size_t*)linkedList->first->value);
	assert(linkedList->first->next == thirdNode);
	assert(valueThree == *(size_t*)linkedList->first->next->value);
	assert(linkedList->first->next->next == secondNode);
	assert(linkedList->first->next->next->value);
	assert(linkedList->first->next->next->next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_release_tests()
{
}

void eskilib_linkedlist_tests()
{
	#ifdef NDEBUG
		eskilib_linkedlist_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_linkedlist_allocate_test", eskilib_linkedlist_allocate_test);

	eskilib_test_run("eskilib_linkedlist_linkednode_allocate_test", eskilib_linkedlist_linkednode_allocate_test);

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
