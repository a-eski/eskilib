#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include "eskilib_doublylinkedlist.h"
#include "eskilib_test.h"

void eskilib_doublylinkedlist_allocate_test()
{
	eskilib_DoublyLinkedList* linkedList = eskilib_doublylinkedlist_allocate();

	assert(linkedList != NULL);
	assert(linkedList->First == NULL);
	assert(linkedList->Last == NULL);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == node);
	assert(*(size_t*)linkedList->First->Value == value);

	assert(linkedList->Last == node);
	assert(*(size_t*)linkedList->Last->Value == value);
	assert(linkedList->Last->Next == NULL);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == nodeTwo);
	assert(linkedList->First->Next == nodeOne);
	assert(*(size_t*)linkedList->First->Value == valueTwo);

	assert(linkedList->Last->Previous == nodeTwo);
	assert(linkedList->Last == nodeOne);
	assert(linkedList->Last->Next == NULL);
	assert(*(size_t*)linkedList->Last->Value == valueOne);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == node);
	assert(*(size_t*)linkedList->First->Value == value);

	assert(linkedList->Last == node);
	assert(*(size_t*)linkedList->Last->Value == value);
	assert(linkedList->Last->Next == NULL);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == nodeOne);
	assert(linkedList->First->Next == nodeTwo);
	assert(*(size_t*)linkedList->First->Value == valueOne);

	assert(linkedList->Last->Previous == nodeOne);
	assert(linkedList->Last == nodeTwo);
	assert(linkedList->Last->Next == NULL);
	assert(*(size_t*)linkedList->Last->Value == valueTwo);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == currentNode);
	assert(linkedList->First->Next == nodeToSetAfter);
	assert(*(size_t*)linkedList->First->Value == valueOne);

	assert(nodeToSetAfter->Previous == currentNode);
	assert(nodeToSetAfter->Next == NULL);
	assert(*(size_t*)nodeToSetAfter->Value = valueTwo);

	assert(linkedList->Last->Previous == currentNode);
	assert(linkedList->Last == nodeToSetAfter);
	assert(linkedList->Last->Next == NULL);
	assert(*(size_t*)linkedList->Last->Value == valueTwo);

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

	assert(linkedList->First->Previous == NULL);
	assert(linkedList->First == firstNode);
	assert(linkedList->First->Next == nodeToSetAfter);
	assert(*(size_t*)linkedList->First->Value == valueOne);

	assert(nodeToSetAfter->Previous = firstNode);
	assert(*(size_t*)nodeToSetAfter->Value == valueTwo);
	assert(nodeToSetAfter->Next = lastNode);
	
	assert(linkedList->Last == lastNode);
	assert(linkedList->Last->Previous == nodeToSetAfter);
	assert(linkedList->Last == lastNode);
	assert(linkedList->Last->Next == NULL);
	assert(*(size_t*)linkedList->Last->Value == valueThree);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_tests()
{
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
