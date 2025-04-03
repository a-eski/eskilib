#include <stddef.h>
#include <stdlib.h>
#include "../eskilib_doublylinkedlist.h"
#include "../etest.h"

void eskilib_doublylinkedlist_malloc_test(void)
{
	eskilib_DoublyLinkedList* linkedList = eskilib_doublylinkedlist_malloc();

	eassert(linkedList != NULL);
	eassert(linkedList->first == NULL);
	eassert(linkedList->last == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_first_empty_list_test(void)
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_doublylinkedlist_malloc();
	node = eskilib_doublylinkedlist_linkednode_malloc(&value);

	eskilib_doublylinkedlist_set_first(node, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == node);
	eassert(*(size_t*)linkedList->first->value == value);

	eassert(linkedList->last == node);
	eassert(*(size_t*)linkedList->last->value == value);
	eassert(linkedList->last->next == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_first_nonempty_list_test(void)
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_malloc();

	nodeOne = eskilib_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeTwo = eskilib_doublylinkedlist_linkednode_malloc(&valueTwo);

	eskilib_doublylinkedlist_set_first(nodeOne, linkedList);
	eskilib_doublylinkedlist_set_first(nodeTwo, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == nodeTwo);
	eassert(linkedList->first->next == nodeOne);
	eassert(*(size_t*)linkedList->first->value == valueTwo);

	eassert(linkedList->last->previous == nodeTwo);
	eassert(linkedList->last == nodeOne);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueOne);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_last_empty_list_test(void)
{

	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_doublylinkedlist_malloc();
	node = eskilib_doublylinkedlist_linkednode_malloc(&value);

	eskilib_doublylinkedlist_set_last(node, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == node);
	eassert(*(size_t*)linkedList->first->value == value);

	eassert(linkedList->last == node);
	eassert(*(size_t*)linkedList->last->value == value);
	eassert(linkedList->last->next == NULL);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_last_nonempty_list_test(void)
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_malloc();

	nodeOne = eskilib_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeTwo = eskilib_doublylinkedlist_linkednode_malloc(&valueTwo);

	eskilib_doublylinkedlist_set_last(nodeOne, linkedList);
	eskilib_doublylinkedlist_set_last(nodeTwo, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == nodeOne);
	eassert(linkedList->first->next == nodeTwo);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(linkedList->last->previous == nodeOne);
	eassert(linkedList->last == nodeTwo);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueTwo);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_after_single_entry_list_test(void)
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_doublylinkedlist_malloc();

	currentNode = eskilib_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeToSetAfter = eskilib_doublylinkedlist_linkednode_malloc(&valueTwo);

	eskilib_doublylinkedlist_set_first(currentNode, linkedList);
	eskilib_doublylinkedlist_set_after(currentNode, nodeToSetAfter, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == currentNode);
	eassert(linkedList->first->next == nodeToSetAfter);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(nodeToSetAfter->previous == currentNode);
	eassert(nodeToSetAfter->next == NULL);
	eassert(*(size_t*)nodeToSetAfter->value = valueTwo);

	eassert(linkedList->last->previous == currentNode);
	eassert(linkedList->last == nodeToSetAfter);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueTwo);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_set_after_in_middle_of_list_test(void)
{
	eskilib_DoublyLinkedList* linkedList = NULL;
	eskilib_DoublyLinkedList_LinkedNode* firstNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	eskilib_DoublyLinkedList_LinkedNode* lastNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;

	linkedList = eskilib_doublylinkedlist_malloc();

	firstNode = eskilib_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeToSetAfter = eskilib_doublylinkedlist_linkednode_malloc(&valueTwo);
	lastNode = eskilib_doublylinkedlist_linkednode_malloc(&valueThree);

	eskilib_doublylinkedlist_set_first(firstNode, linkedList);
	eskilib_doublylinkedlist_set_last(lastNode, linkedList);
	eskilib_doublylinkedlist_set_after(firstNode, nodeToSetAfter, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == firstNode);
	eassert(linkedList->first->next == nodeToSetAfter);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(nodeToSetAfter->previous = firstNode);
	eassert(*(size_t*)nodeToSetAfter->value == valueTwo);
	eassert(nodeToSetAfter->next = lastNode);

	eassert(linkedList->last == lastNode);
	eassert(linkedList->last->previous == nodeToSetAfter);
	eassert(linkedList->last == lastNode);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueThree);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_tests(void)
{
	etest_start();

	etest_run(eskilib_doublylinkedlist_malloc_test);
	etest_run(eskilib_doublylinkedlist_set_first_empty_list_test);
	etest_run(eskilib_doublylinkedlist_set_first_nonempty_list_test);
	etest_run(eskilib_doublylinkedlist_set_last_empty_list_test);
	etest_run(eskilib_doublylinkedlist_set_last_nonempty_list_test);
	etest_run(eskilib_doublylinkedlist_set_after_single_entry_list_test);
	etest_run(eskilib_doublylinkedlist_set_after_in_middle_of_list_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	eskilib_doublylinkedlist_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
