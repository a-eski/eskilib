#ifndef eski_doublylinkedlist_h
#define eski_doublylinkedlist_h

enum eski_DoublyLinkedList_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct eski_DoublyLinkedList_LinkedNode_of_void_star
{
	void* value;
	struct eski_DoublyLinkedList_LinkedNode_of_void_star* next;
	struct eski_DoublyLinkedList_LinkedNode_of_void_star* previous;
} eski_DoublyLinkedList_LinkedNode;

typedef struct
{
	eski_DoublyLinkedList_LinkedNode* first;
	eski_DoublyLinkedList_LinkedNode* last;
} eski_DoublyLinkedList;

eski_DoublyLinkedList* eski_doublylinkedlist_malloc(void);

void eski_doublylinkedlist_free(eski_DoublyLinkedList* linkedList);

eski_DoublyLinkedList_LinkedNode* eski_doublylinkedlist_linkednode_malloc(void* value);

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_first(eski_DoublyLinkedList_LinkedNode* nodeToSetFirst, eski_DoublyLinkedList* linkedList);

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_last(eski_DoublyLinkedList_LinkedNode* nodeToSetLast, eski_DoublyLinkedList* linkedList);

enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_after(eski_DoublyLinkedList_LinkedNode* currentNode,
					eski_DoublyLinkedList_LinkedNode* nodeToSetAfter,
					eski_DoublyLinkedList* linkedList);

/*
enum eski_DoublyLinkedList_Result eski_doublylinkedlist_set_before(eski_DoublyLinkedList_LinkedNode* currentNode, eski_DoublyLinkedList_LinkedNode* nodeToSetBefore);
*/

#endif /* !eski_doublylinkedlist_h */
