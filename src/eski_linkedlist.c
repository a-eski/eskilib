// Copyright (c) eski by Alex Eski 2024

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eski_error_handler.h"
#include "eski_linkedlist.h"

eski_LinkedList* eski_linkedlist_malloc(void)
{
	eski_LinkedList* linkedList = malloc(sizeof(eski_LinkedList));

	if (linkedList == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_LinkedList.\n");

	linkedList->first = NULL;

	return linkedList;
}

void eski_linkedlist_free(eski_LinkedList* linkedList)
{
	eski_LinkedList_LinkedNode* currentNode = NULL;
	eski_LinkedList_LinkedNode* previousNode = NULL;

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

eski_LinkedList_LinkedNode* eski_linkedlist_linkednode_malloc(void* value)
{
	eski_LinkedList_LinkedNode* node = malloc(sizeof(eski_LinkedList_LinkedNode));

	if (node == NULL)
		eski_output_allocation_error_and_exit("Failed to allocate eski_LinkedList_LinkedNode.\n");

	node->value = value;
	node->next = NULL;

	return node;
}

enum eski_LinkedList_Result eski_linkedlist_set_first(eski_LinkedList_LinkedNode* nodeToSetFirst, eski_LinkedList* linkedList)
{
	eski_LinkedList_LinkedNode* temporaryNode = NULL;

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
enum eski_LinkedList_Result eski_linkedlist_set_last(eski_LinkedList_LinkedNode* nodeToSetLast, eski_LinkedList* linkedList)
{
	eski_LinkedList_LinkedNode* currentNode = NULL;

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

enum eski_LinkedList_Result eski_linkedlist_set_after(eski_LinkedList_LinkedNode* currentNode, eski_LinkedList_LinkedNode* nodeToSetAfter)
{
	eski_LinkedList_LinkedNode* temporaryNode = NULL;

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
