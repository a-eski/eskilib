#ifndef eskilib_doublylinkedlist_h
#define eskilib_doublylinkedlist_h

typedef struct eskilib_DoublyLinkedList_LinkedNode_of_void_star
{
	void* Value;
	struct eskilib_DoublyLinkedList_LinkedNode_of_void_star* Next;
	struct eskilib_DoublyLinkedList_LinkedNode_of_void_star* Previous;
} eskilib_DoublyLinkedList_LinkedNode;

typedef struct
{
	eskilib_DoublyLinkedList_LinkedNode* First;
	eskilib_DoublyLinkedList_LinkedNode* Last;
} eskilib_DoublyLinkedList;

eskilib_DoublyLinkedList* eskilib_doublylinkedlist_allocate();

void eskilib_doublylinkedlist_free(eskilib_DoublyLinkedList* linkedList);


eskilib_DoublyLinkedList_LinkedNode* eskilib_doublylinkedlist_linkednode_allocate(void* value);

bool eskilib_doublylinkedlist_set_first(eskilib_DoublyLinkedList_LinkedNode* nodeToSetFirst, eskilib_DoublyLinkedList* linkedList);

bool eskilib_doublylinkedlist_set_last(eskilib_DoublyLinkedList_LinkedNode* nodeToSetLast, eskilib_DoublyLinkedList* linkedList);

bool eskilib_doublylinkedlist_set_after(eskilib_DoublyLinkedList_LinkedNode* currentNode,
					eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eskilib_DoublyLinkedList* linkedList);

/*
bool eskilib_doublylinkedlist_set_before(eskilib_DoublyLinkedList_LinkedNode* currentNode, eskilib_DoublyLinkedList_LinkedNode* nodeToSetBefore);
*/
#endif /* !eskilib_doublylinkedlist_h */

