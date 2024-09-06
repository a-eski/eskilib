#ifndef eskilib_doublylinkedlist_h
#define eskilib_doublylinkedlist_h

enum eskilib_DoublyLinkedList_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct eskilib_DoublyLinkedList_LinkedNode_of_void_star
{
	void* value;
	struct eskilib_DoublyLinkedList_LinkedNode_of_void_star* next;
	struct eskilib_DoublyLinkedList_LinkedNode_of_void_star* previous;
} eskilib_DoublyLinkedList_LinkedNode;

typedef struct
{
	eskilib_DoublyLinkedList_LinkedNode* first;
	eskilib_DoublyLinkedList_LinkedNode* last;
} eskilib_DoublyLinkedList;

eskilib_DoublyLinkedList* eskilib_doublylinkedlist_malloc(void);

void eskilib_doublylinkedlist_free(eskilib_DoublyLinkedList* linkedList);

eskilib_DoublyLinkedList_LinkedNode* eskilib_doublylinkedlist_linkednode_malloc(void* value);

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_first(eskilib_DoublyLinkedList_LinkedNode* nodeToSetFirst, eskilib_DoublyLinkedList* linkedList);

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_last(eskilib_DoublyLinkedList_LinkedNode* nodeToSetLast, eskilib_DoublyLinkedList* linkedList);

enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_after(eskilib_DoublyLinkedList_LinkedNode* currentNode,
					eskilib_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eskilib_DoublyLinkedList* linkedList);

/*
enum eskilib_DoublyLinkedList_Result eskilib_doublylinkedlist_set_before(eskilib_DoublyLinkedList_LinkedNode* currentNode, eskilib_DoublyLinkedList_LinkedNode* nodeToSetBefore);
*/

#endif /* !eskilib_doublylinkedlist_h */

