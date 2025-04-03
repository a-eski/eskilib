#include <stdlib.h>
#include <assert.h>

#include "edllist.h"

edllist* edllist_malloc(void)
{
	edllist* linkedList = malloc(sizeof(edllist));

	if (linkedList == NULL) {
		return NULL;
	}

	linkedList->first = NULL;
	linkedList->last = NULL;

	return linkedList;
}

void edllist_free(edllist* linkedList)
{
	edllist_LinkedNode* currentNode = NULL;
	edllist_LinkedNode* previousNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL) {
		return;
	}

	currentNode = linkedList->first;

	while (currentNode != NULL)
	{
		previousNode = currentNode;
		currentNode = currentNode->next;
		free(previousNode);
	}

	free(linkedList);
}

edllist_LinkedNode* edllist_linkednode_malloc(void* value)
{
	edllist_LinkedNode* node = NULL;

	assert(value != NULL);
	if (value == NULL) {
		return NULL;
	}

	node = malloc(sizeof(edllist_LinkedNode));

	if (node == NULL) {
		return NULL;
	}

	node->value = value;
	node->next = NULL;
	node->previous = NULL;

	return node;
}

enum edllist_Result edllist_set_first(edllist_LinkedNode* nodeToSetFirst, edllist* linkedList)
{
	edllist_LinkedNode* temporaryNode = NULL;

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

enum edllist_Result edllist_set_last(edllist_LinkedNode* nodeToSetLast, edllist* linkedList)
{
	edllist_LinkedNode* temporaryNode = NULL;

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

enum edllist_Result edllist_set_after(edllist_LinkedNode* currentNode,
					edllist_LinkedNode* nodeToSetAfter,
					edllist* linkedList)
{
	edllist_LinkedNode* temporaryNode = NULL;

	assert(currentNode != NULL);
	if (currentNode == NULL)
		return FAILURE_NULL_NODE;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return FAILURE_NULL_NODE;

	if (currentNode == linkedList->last)
		return edllist_set_last(nodeToSetAfter, linkedList);

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
