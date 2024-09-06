#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"
#include "eskilib_linkedlist.h"

eskilib_LinkedList* eskilib_linkedlist_malloc()
{
	eskilib_LinkedList* linkedList = malloc(sizeof(eskilib_LinkedList));

	if (linkedList == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_LinkedList.\n");

	linkedList->first = NULL;

	return linkedList;
}

void eskilib_linkedlist_free(eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* currentNode = NULL;
	eskilib_LinkedList_LinkedNode* previousNode = NULL;

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

eskilib_LinkedList_LinkedNode* eskilib_linkedlist_linkednode_malloc(void* value)
{
	eskilib_LinkedList_LinkedNode* node = malloc(sizeof(eskilib_LinkedList_LinkedNode));
	
	if (node == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_LinkedList_LinkedNode.\n");

	node->value = value;
	node->next = NULL;

	return node;
}

enum eskilib_LinkedList_Result eskilib_linkedlist_set_first(eskilib_LinkedList_LinkedNode* nodeToSetFirst, eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return FAILURE_NULL_LINKEDLIST;

	assert(nodeToSetFirst != NULL);
	if (nodeToSetFirst == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetFirst->next == NULL);
	if (nodeToSetFirst->next != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	if (linkedList->first == NULL)
	{
		linkedList->first = nodeToSetFirst;
		return SUCCESS;
	}

	temporaryNode = linkedList->first;
	linkedList->first = nodeToSetFirst;
	linkedList->first->next = temporaryNode;

	return SUCCESS;
}

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
enum eskilib_LinkedList_Result eskilib_linkedlist_set_last(eskilib_LinkedList_LinkedNode* nodeToSetLast, eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* currentNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return FAILURE_NULL_LINKEDLIST;

	assert(nodeToSetLast != NULL);
	if (nodeToSetLast == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetLast->next == NULL);
	if (nodeToSetLast->next != NULL)
		return FAILURE_ALREADY_LINKED_NODE;

	if (linkedList->first == NULL)
	{
		linkedList->first = nodeToSetLast;
		return SUCCESS;
	}

	currentNode = linkedList->first;
	
	while (currentNode->next != NULL)
	{
		currentNode = currentNode->next;
	}

	currentNode->next = nodeToSetLast;
	nodeToSetLast->next = NULL;

	return SUCCESS;
}

enum eskilib_LinkedList_Result eskilib_linkedlist_set_after(eskilib_LinkedList_LinkedNode* currentNode, eskilib_LinkedList_LinkedNode* nodeToSetAfter)
{
	eskilib_LinkedList_LinkedNode* temporaryNode = NULL;

	assert(currentNode != NULL);
	if (currentNode == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return FAILURE_NULL_NODE;

	temporaryNode = currentNode->next;
	currentNode->next = nodeToSetAfter;
	nodeToSetAfter->next = temporaryNode;

	return SUCCESS;
}
