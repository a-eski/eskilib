#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eskilib_error_handler.h"
#include "eskilib_linkedlist.h"

eskilib_LinkedList* eskilib_linkedlist_allocate()
{
	eskilib_LinkedList* linkedList = malloc(sizeof(eskilib_LinkedList));

	if (linkedList == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_LinkedList.\n");

	linkedList->First = NULL;

	return linkedList;
}

void eskilib_linkedlist_free(eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* currentNode = NULL;
	eskilib_LinkedList_LinkedNode* previousNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return;

	currentNode = linkedList->First;

	while (currentNode != NULL)
	{
		previousNode = currentNode;
		currentNode = currentNode->Next;	
		free(previousNode);
	}

	free(linkedList);
}

eskilib_LinkedList_LinkedNode* eskilib_linkedlist_linkednode_allocate(void* value)
{
	eskilib_LinkedList_LinkedNode* node = malloc(sizeof(eskilib_LinkedList_LinkedNode));
	
	if (node == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_LinkedList_LinkedNode.\n");

	node->Value = value;
	node->Next = NULL;

	return node;
}

bool eskilib_linkedlist_set_first(eskilib_LinkedList_LinkedNode* nodeToSetFirst, eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return false;

	assert(nodeToSetFirst != NULL);
	if (nodeToSetFirst == NULL)
		return false;

	assert(nodeToSetFirst->Next == NULL);
	if (nodeToSetFirst->Next != NULL)
		return false;

	if (linkedList->First == NULL)
	{
		linkedList->First = nodeToSetFirst;
		return true;
	}

	temporaryNode = linkedList->First;
	linkedList->First = nodeToSetFirst;
	linkedList->First->Next = temporaryNode;

	return true;
}

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
bool eskilib_linkedlist_set_last(eskilib_LinkedList_LinkedNode* nodeToSetLast, eskilib_LinkedList* linkedList)
{
	eskilib_LinkedList_LinkedNode* currentNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return false;

	assert(nodeToSetLast != NULL);
	if (nodeToSetLast == NULL)
		return false;

	assert(nodeToSetLast->Next == NULL);
	if (nodeToSetLast->Next != NULL)
		return false;

	if (linkedList->First == NULL)
	{
		linkedList->First = nodeToSetLast;
		return true;
	}

	currentNode = linkedList->First;
	
	while (currentNode->Next != NULL)
	{
		currentNode = currentNode->Next;
	}

	currentNode->Next = nodeToSetLast;
	nodeToSetLast->Next = NULL;

	return true;
}

bool eskilib_linkedlist_set_after(eskilib_LinkedList_LinkedNode* currentNode, eskilib_LinkedList_LinkedNode* nodeToSetAfter)
{
	eskilib_LinkedList_LinkedNode* temporaryNode = NULL;

	assert(currentNode != NULL);
	if (currentNode == NULL)
		return false;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return false;

	temporaryNode = currentNode->Next;
	currentNode->Next = nodeToSetAfter;
	nodeToSetAfter->Next = temporaryNode;

	return true;
}
