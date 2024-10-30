#include <stddef.h>
#include <stdlib.h>
#include "eskilib_doublylinkedlist.h"
#include "eskilib_test.h"

void eskilib_doublylinkedlist_malloc_test(void)
{
	eskilib_DoublyLinkedList* linkedList = eskilib_doublylinkedlist_malloc();

	eskilib_assert(linkedList != NULL);
	eskilib_assert(linkedList->first == NULL);
	eskilib_assert(linkedList->last == NULL);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == node);
	eskilib_assert(*(size_t*)linkedList->first->value == value);

	eskilib_assert(linkedList->last == node);
	eskilib_assert(*(size_t*)linkedList->last->value == value);
	eskilib_assert(linkedList->last->next == NULL);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == nodeTwo);
	eskilib_assert(linkedList->first->next == nodeOne);
	eskilib_assert(*(size_t*)linkedList->first->value == valueTwo);

	eskilib_assert(linkedList->last->previous == nodeTwo);
	eskilib_assert(linkedList->last == nodeOne);
	eskilib_assert(linkedList->last->next == NULL);
	eskilib_assert(*(size_t*)linkedList->last->value == valueOne);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == node);
	eskilib_assert(*(size_t*)linkedList->first->value == value);

	eskilib_assert(linkedList->last == node);
	eskilib_assert(*(size_t*)linkedList->last->value == value);
	eskilib_assert(linkedList->last->next == NULL);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == nodeOne);
	eskilib_assert(linkedList->first->next == nodeTwo);
	eskilib_assert(*(size_t*)linkedList->first->value == valueOne);

	eskilib_assert(linkedList->last->previous == nodeOne);
	eskilib_assert(linkedList->last == nodeTwo);
	eskilib_assert(linkedList->last->next == NULL);
	eskilib_assert(*(size_t*)linkedList->last->value == valueTwo);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == currentNode);
	eskilib_assert(linkedList->first->next == nodeToSetAfter);
	eskilib_assert(*(size_t*)linkedList->first->value == valueOne);

	eskilib_assert(nodeToSetAfter->previous == currentNode);
	eskilib_assert(nodeToSetAfter->next == NULL);
	eskilib_assert(*(size_t*)nodeToSetAfter->value = valueTwo);

	eskilib_assert(linkedList->last->previous == currentNode);
	eskilib_assert(linkedList->last == nodeToSetAfter);
	eskilib_assert(linkedList->last->next == NULL);
	eskilib_assert(*(size_t*)linkedList->last->value == valueTwo);

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

	eskilib_assert(linkedList->first->previous == NULL);
	eskilib_assert(linkedList->first == firstNode);
	eskilib_assert(linkedList->first->next == nodeToSetAfter);
	eskilib_assert(*(size_t*)linkedList->first->value == valueOne);

	eskilib_assert(nodeToSetAfter->previous = firstNode);
	eskilib_assert(*(size_t*)nodeToSetAfter->value == valueTwo);
	eskilib_assert(nodeToSetAfter->next = lastNode);

	eskilib_assert(linkedList->last == lastNode);
	eskilib_assert(linkedList->last->previous == nodeToSetAfter);
	eskilib_assert(linkedList->last == lastNode);
	eskilib_assert(linkedList->last->next == NULL);
	eskilib_assert(*(size_t*)linkedList->last->value == valueThree);

	eskilib_doublylinkedlist_free(linkedList);
}

void eskilib_doublylinkedlist_release_tests(void)
{
}

void eskilib_doublylinkedlist_tests(void)
{
	#ifdef NDEBUG
		eskilib_doublylinkedlist_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_doublylinkedlist_malloc_test", eskilib_doublylinkedlist_malloc_test);

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
