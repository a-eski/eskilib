#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"
#include "eskilib_doublylinkedlist.h"

eskilib_DoublyLinkedList* eskilib_doublylinkedlist_allocate()
{
	eskilib_DoublyLinkedList* linkedList = malloc(sizeof(eskilib_DoublyLinkedList));

	if (linkedList == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_DoublyLinkedList.\n");

	linkedList->first = NULL;
	linkedList->last = NULL;

	return linkedList;
}

void eskilib_doublylinkedlist_free(eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* previousNode = NULL;

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

eskilib_DoublyLinkedList_LinkedNode* eskilib_doublylinkedlist_linkednode_allocate(void* value)
{
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;

	assert(value != NULL);
	if (value == NULL)
		return NULL;

	node = malloc(sizeof(eskilib_DoublyLinkedList_LinkedNode));

	if (node == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_DoublyLinkedList_LinkedNode.\n");

	node->value = value;
	node->next = NULL;
	node->previous = NULL;

	return node;
}

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_first(eskilib_DoublyLinkedList_LinkedNode* nodeToSetFirst, eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

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

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_last(eskilib_DoublyLinkedList_LinkedNode* nodeToSetLast, eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

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

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_after(eskilib_DoublyLinkedList_LinkedNode* currentNode,
					eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;
	
	assert(currentNode != NULL);
	if (currentNode == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return FAILURE_NULL_NODE;

	if (currentNode == linkedList->last)
		return eskilib_doublylinkedlist_set_last(nodeToSetAfter, linkedList);

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
