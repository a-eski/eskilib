#include <stdlib.h>
#include <assert.h>
#include "eski_error_handler.h"
#include "eski_doublylinkedlist.h"

eski_DoublyLinkedList* eski_doublylinkedlist_malloc(void)
{
	eski_DoublyLinkedList* linkedList = malloc(sizeof(eski_DoublyLinkedList));

	if (linkedList == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_DoublyLinkedList.\n");

	linkedList->first = NULL;
	linkedList->last = NULL;

	return linkedList;
}

void eski_doublylinkedlist_free(eski_DoublyLinkedList* linkedList)
{
	eski_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eski_DoublyLinkedList_LinkedNode* previousNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return;

	currentNode = linkedList->first;

	while (currentNode != NULL)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
		free(previousNode);
	}

	free(linkedList);
}

eski_DoublyLinkedList_LinkedNode* eski_doublylinkedlist_linkednode_malloc(void* value)
{
	eski_DoublyLinkedList_LinkedNode* node = NULL;

	assert(value != NULL);
	if (value == NULL)
		return NULL;

	node = malloc(sizeof(eski_DoublyLinkedList_LinkedNode));

	if (node == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_DoublyLinkedList_LinkedNode.\n");

	node->value = value;
	node->next = NULL;
	node->previous = NULL;

	return node;
}

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_first(eski_DoublyLinkedList_LinkedNode* nodeToSetFirst, eski_DoublyLinkedList* linkedList)
{
	eski_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return FAILURE_NULL_LINKEDLIST;

	assert(nodeToSetFirst != NULL);
	if (nodeToSetFirst == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetFirst->next == NULL);
	if (nodeToSetFirst->next != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	assert(nodeToSetFirst->previous == NULL);
	if (nodeToSetFirst->previous != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	if (linkedList->first == NULL)
	{
		linkedList->first = nodeToSetFirst;
		linkedList->first->previous = NULL;
		linkedList->last = nodeToSetFirst;
		linkedList->last->next = NULL;
		return SUCCESS;
	}

	temporaryNode = linkedList->first;
	linkedList->first = nodeToSetFirst;
	linkedList->first->next = temporaryNode;
	linkedList->first->previous = NULL;

	if (temporaryNode == linkedList->last)
	{
		linkedList->last->previous = nodeToSetFirst;
	}

	return SUCCESS;
}

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_last(eski_DoublyLinkedList_LinkedNode* nodeToSetLast, eski_DoublyLinkedList* linkedList)
{
	eski_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return FAILURE_NULL_LINKEDLIST;

	assert(nodeToSetLast != NULL);
	if (nodeToSetLast == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetLast->next == NULL);
	if (nodeToSetLast->next != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	assert(nodeToSetLast->previous == NULL);
	if (nodeToSetLast->previous != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	if (linkedList->last == NULL)
	{
		linkedList->first = nodeToSetLast;
		linkedList->first->previous = NULL;
		linkedList->last = nodeToSetLast;
		linkedList->last->next = NULL;
		return SUCCESS;
	}

	temporaryNode = linkedList->last;
	linkedList->last = nodeToSetLast;
	linkedList->last->next = NULL;
	linkedList->last->previous = temporaryNode;

	if (temporaryNode == linkedList->first)
	{
		linkedList->first->next = nodeToSetLast;
	}

	return SUCCESS;
}

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_after(eski_DoublyLinkedList_LinkedNode* currentNode,
					eski_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eski_DoublyLinkedList* linkedList)
{
	eski_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

	assert(currentNode != NULL);
	if (currentNode == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return FAILURE_NULL_NODE;

	if (currentNode == linkedList->last)
		return eski_doublylinkedlist_set_last(nodeToSetAfter, linkedList);

	assert(nodeToSetAfter->next == NULL);
	if (nodeToSetAfter->next != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	assert(nodeToSetAfter->previous == NULL);
	if (nodeToSetAfter->previous != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	temporaryNode = currentNode->next;
	currentNode->next = nodeToSetAfter;
	nodeToSetAfter->previous = currentNode;
	nodeToSetAfter->next = temporaryNode;
	temporaryNode->previous = nodeToSetAfter;

	return SUCCESS;
}
