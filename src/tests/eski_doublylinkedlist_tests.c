#include <stddef.h>
#include <stdlib.h>
#include "../eski_doublylinkedlist.h"
#include "../eski_test.h"

void eski_doublylinkedlist_malloc_test(void)
{
	eski_DoublyLinkedList* linkedList = eski_doublylinkedlist_malloc();

	eski_assert(linkedList != NULL);
	eski_assert(linkedList->first == NULL);
	eski_assert(linkedList->last == NULL);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_first_empty_list_test(void)
{

	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eski_doublylinkedlist_malloc();
	node = eski_doublylinkedlist_linkednode_malloc(&value);

	eski_doublylinkedlist_set_first(node, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == node);
	eski_assert(*(size_t*)linkedList->first->value == value);

	eski_assert(linkedList->last == node);
	eski_assert(*(size_t*)linkedList->last->value == value);
	eski_assert(linkedList->last->next == NULL);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_first_nonempty_list_test(void)
{

	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eski_doublylinkedlist_malloc();

	nodeOne = eski_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeTwo = eski_doublylinkedlist_linkednode_malloc(&valueTwo);

	eski_doublylinkedlist_set_first(nodeOne, linkedList);
	eski_doublylinkedlist_set_first(nodeTwo, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == nodeTwo);
	eski_assert(linkedList->first->next == nodeOne);
	eski_assert(*(size_t*)linkedList->first->value == valueTwo);

	eski_assert(linkedList->last->previous == nodeTwo);
	eski_assert(linkedList->last == nodeOne);
	eski_assert(linkedList->last->next == NULL);
	eski_assert(*(size_t*)linkedList->last->value == valueOne);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_last_empty_list_test(void)
{

	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eski_doublylinkedlist_malloc();
	node = eski_doublylinkedlist_linkednode_malloc(&value);

	eski_doublylinkedlist_set_last(node, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == node);
	eski_assert(*(size_t*)linkedList->first->value == value);

	eski_assert(linkedList->last == node);
	eski_assert(*(size_t*)linkedList->last->value == value);
	eski_assert(linkedList->last->next == NULL);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_last_nonempty_list_test(void)
{
	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeOne = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eski_doublylinkedlist_malloc();

	nodeOne = eski_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeTwo = eski_doublylinkedlist_linkednode_malloc(&valueTwo);

	eski_doublylinkedlist_set_last(nodeOne, linkedList);
	eski_doublylinkedlist_set_last(nodeTwo, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == nodeOne);
	eski_assert(linkedList->first->next == nodeTwo);
	eski_assert(*(size_t*)linkedList->first->value == valueOne);

	eski_assert(linkedList->last->previous == nodeOne);
	eski_assert(linkedList->last == nodeTwo);
	eski_assert(linkedList->last->next == NULL);
	eski_assert(*(size_t*)linkedList->last->value == valueTwo);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_after_single_entry_list_test(void)
{
	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eski_doublylinkedlist_malloc();

	currentNode = eski_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeToSetAfter = eski_doublylinkedlist_linkednode_malloc(&valueTwo);

	eski_doublylinkedlist_set_first(currentNode, linkedList);
	eski_doublylinkedlist_set_after(currentNode, nodeToSetAfter, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == currentNode);
	eski_assert(linkedList->first->next == nodeToSetAfter);
	eski_assert(*(size_t*)linkedList->first->value == valueOne);

	eski_assert(nodeToSetAfter->previous == currentNode);
	eski_assert(nodeToSetAfter->next == NULL);
	eski_assert(*(size_t*)nodeToSetAfter->value = valueTwo);

	eski_assert(linkedList->last->previous == currentNode);
	eski_assert(linkedList->last == nodeToSetAfter);
	eski_assert(linkedList->last->next == NULL);
	eski_assert(*(size_t*)linkedList->last->value == valueTwo);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_set_after_in_middle_of_list_test(void)
{
	eski_DoublyLinkedList* linkedList = NULL;
	eski_DoublyLinkedList_LinkedNode* firstNode = NULL;
	eski_DoublyLinkedList_LinkedNode* nodeToSetAfter = NULL;
	eski_DoublyLinkedList_LinkedNode* lastNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;

	linkedList = eski_doublylinkedlist_malloc();

	firstNode = eski_doublylinkedlist_linkednode_malloc(&valueOne);
	nodeToSetAfter = eski_doublylinkedlist_linkednode_malloc(&valueTwo);
	lastNode = eski_doublylinkedlist_linkednode_malloc(&valueThree);

	eski_doublylinkedlist_set_first(firstNode, linkedList);
	eski_doublylinkedlist_set_last(lastNode, linkedList);
	eski_doublylinkedlist_set_after(firstNode, nodeToSetAfter, linkedList);

	eski_assert(linkedList->first->previous == NULL);
	eski_assert(linkedList->first == firstNode);
	eski_assert(linkedList->first->next == nodeToSetAfter);
	eski_assert(*(size_t*)linkedList->first->value == valueOne);

	eski_assert(nodeToSetAfter->previous = firstNode);
	eski_assert(*(size_t*)nodeToSetAfter->value == valueTwo);
	eski_assert(nodeToSetAfter->next = lastNode);

	eski_assert(linkedList->last == lastNode);
	eski_assert(linkedList->last->previous == nodeToSetAfter);
	eski_assert(linkedList->last == lastNode);
	eski_assert(linkedList->last->next == NULL);
	eski_assert(*(size_t*)linkedList->last->value == valueThree);

	eski_doublylinkedlist_free(linkedList);
}

void eski_doublylinkedlist_release_tests(void)
{
}

void eski_doublylinkedlist_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_doublylinkedlist_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_doublylinkedlist_malloc_test", eski_doublylinkedlist_malloc_test);

	eski_test_run("eski_doublylinkedlist_set_first_empty_list_test", eski_doublylinkedlist_set_first_empty_list_test);

	eski_test_run("eski_doublylinkedlist_set_first_nonempty_list_test", eski_doublylinkedlist_set_first_nonempty_list_test);

	eski_test_run("eski_doublylinkedlist_set_last_empty_list_test", eski_doublylinkedlist_set_last_empty_list_test);

	eski_test_run("eski_doublylinkedlist_set_last_nonempty_list_test", eski_doublylinkedlist_set_last_nonempty_list_test);

	eski_test_run("eski_doublylinkedlist_set_after_single_entry_list_test", eski_doublylinkedlist_set_after_single_entry_list_test);

	eski_test_run("eski_doublylinkedlist_set_after_in_middle_of_list_test", eski_doublylinkedlist_set_after_in_middle_of_list_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_doublylinkedlist_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
