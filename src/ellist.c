/* Copyright (C) eskilib by Alex Eski 2024 */

#include <stdlib.h>
#include <assert.h>

#include "ellist.h"

ellist* ellist_malloc(void)
{
	ellist* llist = malloc(sizeof(ellist));

	if (!llist) {
		return NULL;
	}

	llist->first = NULL;

	return llist;
}

void ellist_free(ellist* llist)
{
	ellist_Node* currentNode = NULL;
	ellist_Node* previousNode = NULL;

	assert(llist);
	if (!llist) {
		return;
	}

	currentNode = llist->first;

	while (currentNode) {
		previousNode = currentNode;
		currentNode = currentNode->next;
		free(previousNode);
	}

	free(llist);
}

ellist_Node* ellist_linkednode_malloc(void* value)
{
	ellist_Node* node = malloc(sizeof(ellist_Node));

	if (!node) {
		return NULL;
	}

	node->value = value;
	node->next = NULL;

	return node;
}

enum ellist_Result ellist_set_first(ellist_Node* nodeToSetFirst, ellist* llist)
{
	ellist_Node* temporaryNode = NULL;

	assert(llist);
	if (!llist) {
		return FAILURE_NULL_LINKEDLIST;
	}

	assert(nodeToSetFirst);
	if (!nodeToSetFirst) {
		return FAILURE_NULL_NODE;
	}

	assert(!nodeToSetFirst->next);
	if (nodeToSetFirst->next) {
		return FAILURE_ALREADY_LINKED_NODE;
	}

	if (!llist->first) {
		llist->first = nodeToSetFirst;
		return SUCCESS;
	}

	temporaryNode = llist->first;
	llist->first = nodeToSetFirst;
	llist->first->next = temporaryNode;

	return SUCCESS;
}

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
enum ellist_Result ellist_set_last(ellist_Node* nodeToSetLast, ellist* llist)
{
	ellist_Node* currentNode = NULL;

	assert(llist);
	if (!llist) {
		return FAILURE_NULL_LINKEDLIST;
	}

	assert(nodeToSetLast);
	if (!nodeToSetLast) {
		return FAILURE_NULL_NODE;
	}

	assert(!nodeToSetLast->next);
	if (nodeToSetLast->next) {
		return FAILURE_ALREADY_LINKED_NODE;
	}

	if (!llist->first) {
		llist->first = nodeToSetLast;
		return SUCCESS;
	}

	currentNode = llist->first;

	while (currentNode->next) {
		currentNode = currentNode->next;
	}

	currentNode->next = nodeToSetLast;
	nodeToSetLast->next = NULL;

	return SUCCESS;
}

enum ellist_Result ellist_set_after(ellist_Node* currentNode, ellist_Node* nodeToSetAfter)
{
	ellist_Node* temporaryNode = NULL;

	assert(currentNode);
	if (!currentNode) {
		return FAILURE_NULL_NODE;
	}

	assert(nodeToSetAfter);
	if (!nodeToSetAfter) {
		return FAILURE_NULL_NODE;
	}

	temporaryNode = currentNode->next;
	currentNode->next = nodeToSetAfter;
	nodeToSetAfter->next = temporaryNode;

	return SUCCESS;
}
