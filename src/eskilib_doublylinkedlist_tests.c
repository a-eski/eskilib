#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include "eskilib_doublylinkedlist.h"
#include "eskilib_test.h"

void eskilib_doublylinkedlist_allocate_test()
{
	eskilib_DoublyLinkedList* linkedList = eskilib_doublylinkedlist_allocate();

	assert(linkedList != NULL);
	assert(linkedList->first == NULL);
	assert(linkedList->last == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_first_empty_list_test()
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_doublylinkedlist_allocate();
	node = eskilib_doublylinkedlist_linkednode_allocate(&value);

	eskilib_doublylinkedlist_set_first(node, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == node);
	assert(*(size_t*)linkedList->first->value == value);

	assert(linkedList->last == node);
	assert(*(size_t*)linkedList->last->value == value);
	assert(linkedList->last->next == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_first_nonempty_list_test()
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_allocate();

	nodeOne = eskilib_doublylinkedlist_linkednode_allocate(&valueOne);
	nodeTwo = eskilib_doublylinkedlist_linkednode_allocate(&valueTwo);

	eskilib_doublylinkedlist_set_first(nodeOne, linkedList);
	eskilib_doublylinkedlist_set_first(nodeTwo, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == nodeTwo);
	assert(linkedList->first->next == nodeOne);
	assert(*(size_t*)linkedList->first->value == valueTwo);

	assert(linkedList->last->previous == nodeTwo);
	assert(linkedList->last == nodeOne);
	assert(linkedList->last->next == NULL);
	assert(*(size_t*)linkedList->last->value == valueOne);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_last_empty_list_test()
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_doublylinkedlist_allocate();
	node = eskilib_doublylinkedlist_linkednode_allocate(&value);

	eskilib_doublylinkedlist_set_last(node, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == node);
	assert(*(size_t*)linkedList->first->value == value);

	assert(linkedList->last == node);
	assert(*(size_t*)linkedList->last->value == value);
	assert(linkedList->last->next == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_last_nonempty_list_test()
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_allocate();

	nodeOne = eskilib_doublylinkedlist_linkednode_allocate(&valueOne);
	nodeTwo = eskilib_doublylinkedlist_linkednode_allocate(&valueTwo);

	eskilib_doublylinkedlist_set_last(nodeOne, linkedList);
	eskilib_doublylinkedlist_set_last(nodeTwo, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == nodeOne);
	assert(linkedList->first->next == nodeTwo);
	assert(*(size_t*)linkedList->first->value == valueOne);

	assert(linkedList->last->previous == nodeOne);
	assert(linkedList->last == nodeTwo);
	assert(linkedList->last->next == NULL);
	assert(*(size_t*)linkedList->last->value == valueTwo);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_after_single_entry_list_test()
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_allocate();

	currentNode = eskilib_doublylinkedlist_linkednode_allocate(&valueOne);
	nodeToSetAfter = eskilib_doublylinkedlist_linkednode_allocate(&valueTwo);

	eskilib_doublylinkedlist_set_first(currentNode, linkedList);
	eskilib_doublylinkedlist_set_after(currentNode, nodeToSetAfter, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == currentNode);
	assert(linkedList->first->next == nodeToSetAfter);
	assert(*(size_t*)linkedList->first->value == valueOne);

	assert(nodeToSetAfter->previous == currentNode);
	assert(nodeToSetAfter->next == NULL);
	assert(*(size_t*)nodeToSetAfter->value = valueTwo);

	assert(linkedList->last->previous == currentNode);
	assert(linkedList->last == nodeToSetAfter);
	assert(linkedList->last->next == NULL);
	assert(*(size_t*)linkedList->last->value == valueTwo);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_after_in_middle_of_list_test()
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* firstNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	eskilib_DoublyLinkedList_LinkedNode* lastNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;

	linkedList = eskilib_doublylinkedlist_allocate();

	firstNode = eskilib_doublylinkedlist_linkednode_allocate(&valueOne);
	nodeToSetAfter = eskilib_doublylinkedlist_linkednode_allocate(&valueTwo);
	lastNode = eskilib_doublylinkedlist_linkednode_allocate(&valueThree);

	eskilib_doublylinkedlist_set_first(firstNode, linkedList);
	eskilib_doublylinkedlist_set_last(lastNode, linkedList);
	eskilib_doublylinkedlist_set_after(firstNode, nodeToSetAfter, linkedList);

	assert(linkedList->first->previous == NULL);
	assert(linkedList->first == firstNode);
	assert(linkedList->first->next == nodeToSetAfter);
	assert(*(size_t*)linkedList->first->value == valueOne);

	assert(nodeToSetAfter->previous = firstNode);
	assert(*(size_t*)nodeToSetAfter->value == valueTwo);
	assert(nodeToSetAfter->next = lastNode);
	
	assert(linkedList->last == lastNode);
	assert(linkedList->last->previous == nodeToSetAfter);
	assert(linkedList->last == lastNode);
	assert(linkedList->last->next == NULL);
	assert(*(size_t*)linkedList->last->value == valueThree);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_release_tests()
{
}

void eskilib_doublylinkedlist_tests()
{
	#ifdef NDEBUG
		eskilib_doublylinkedlist_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_doublylinkedlist_allocate_test", eskilib_doublylinkedlist_allocate_test);

	eskilib_test_run("eskilib_doublylinkedlist_set_first_empty_list_test", eskilib_doublylinkedlist_set_first_empty_list_test);
	
	eskilib_test_run("eskilib_doublylinkedlist_set_first_nonempty_list_test", eskilib_doublylinkedlist_set_first_nonempty_list_test);
	
	eskilib_test_run("eskilib_doublylinkedlist_set_last_empty_list_test", eskilib_doublylinkedlist_set_last_empty_list_test);
	
	eskilib_test_run("eskilib_doublylinkedlist_set_last_nonempty_list_test", eskilib_doublylinkedlist_set_last_nonempty_list_test);

	eskilib_test_run("eskilib_doublylinkedlist_set_after_single_entry_list_test", eskilib_doublylinkedlist_set_after_single_entry_list_test);

	eskilib_test_run("eskilib_doublylinkedlist_set_after_in_middle_of_list_test", eskilib_doublylinkedlist_set_after_in_middle_of_list_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_doublylinkedlist_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
