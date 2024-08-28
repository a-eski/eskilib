#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "eskilib_error_handler.h"
#include "eskilib_doublylinkedlist.h"

eskilib_DoublyLinkedList* eskilib_doublylinkedlist_allocate()
{
	eskilib_DoublyLinkedList* linkedList = malloc(sizeof(eskilib_DoublyLinkedList));

	if (linkedList == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_DoublyLinkedList.\n");

	linkedList->First = NULL;
	linkedList->Last = NULL;

	return linkedList;
}

void eskilib_doublylinkedlist_free(eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* currentNode = NULL;
	eskilib_DoublyLinkedList_LinkedNode* previousNode = NULL;

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

eskilib_DoublyLinkedList_LinkedNode* eskilib_doublylinkedlist_linkednode_allocate(void* value)
{
	eskilib_DoublyLinkedList_LinkedNode* node = NULL;

	assert(value != NULL);
	if (value == NULL)
		return NULL;

	node = malloc(sizeof(eskilib_DoublyLinkedList_LinkedNode));

	if (node == NULL)
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_DoublyLinkedList_LinkedNode.\n");

	node->Value = value;
	node->Next = NULL;
	node->Previous = NULL;

	return node;
}

bool eskilib_doublylinkedlist_set_first(eskilib_DoublyLinkedList_LinkedNode* nodeToSetFirst, eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return false;

	assert(nodeToSetFirst != NULL);
	if (nodeToSetFirst == NULL)
		return false;

	assert(nodeToSetFirst->Next == NULL);
	if (nodeToSetFirst->Next != NULL)
		return false;

	assert(nodeToSetFirst->Previous == NULL);
	if (nodeToSetFirst->Previous != NULL)
		return false;

	if (linkedList->First == NULL)
	{
		linkedList->First = nodeToSetFirst;
		linkedList->First->Previous = NULL;
		linkedList->Last = nodeToSetFirst;
		linkedList->Last->Next = NULL;
		return true;
	}

	temporaryNode = linkedList->First;
	linkedList->First = nodeToSetFirst;
	linkedList->First->Next = temporaryNode;
	linkedList->First->Previous = NULL;

	if (temporaryNode == linkedList->Last)
	{
		linkedList->Last->Previous = nodeToSetFirst;		
	}

	return true;
}

bool eskilib_doublylinkedlist_set_last(eskilib_DoublyLinkedList_LinkedNode* nodeToSetLast, eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;

	assert(linkedList != NULL);
	if (linkedList == NULL)
		return false;

	assert(nodeToSetLast != NULL);
	if (nodeToSetLast == NULL)
		return false;

	assert(nodeToSetLast->Next == NULL);
	if (nodeToSetLast->Next != NULL)
		return false;

	assert(nodeToSetLast->Previous == NULL);
	if (nodeToSetLast->Previous != NULL)
		return false;

	if (linkedList->Last == NULL)
	{
		linkedList->First = nodeToSetLast;
		linkedList->First->Previous = NULL;
		linkedList->Last = nodeToSetLast;
		linkedList->Last->Next = NULL;
		return true;
	}

	temporaryNode = linkedList->Last;
	linkedList->Last = nodeToSetLast;
	linkedList->Last->Next = NULL;
	linkedList->Last->Previous = temporaryNode;

	if (temporaryNode == linkedList->First)
	{
		linkedList->First->Next = nodeToSetLast;
	}

	return true;
}

bool eskilib_doublylinkedlist_set_after(eskilib_DoublyLinkedList_LinkedNode* currentNode,
					eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eskilib_DoublyLinkedList* linkedList)
{
	eskilib_DoublyLinkedList_LinkedNode* temporaryNode = NULL;
	
	assert(currentNode != NULL);
	if (currentNode == NULL)
		return false;

	assert(nodeToSetAfter != NULL);
	if (nodeToSetAfter == NULL)
		return false;

	if (currentNode == linkedList->Last)
		return eskilib_doublylinkedlist_set_last(nodeToSetAfter, linkedList);

	temporaryNode = currentNode->Next;
	currentNode->Next = nodeToSetAfter;
	nodeToSetAfter->Previous = currentNode;
	nodeToSetAfter->Next = temporaryNode;
	temporaryNode->Previous = nodeToSetAfter;
	
	return true;
}
