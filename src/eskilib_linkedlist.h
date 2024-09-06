#ifndef eskilib_linkedlist_h
#define eskilib_linkedlist_h

enum eskilib_LinkedList_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct eskilib_LinkedList_LinkedNode_of_void_star
{
	void* value;
	struct eskilib_LinkedList_LinkedNode_of_void_star* next;
} eskilib_LinkedList_LinkedNode;

typedef struct
{
	eskilib_LinkedList_LinkedNode* first;
} eskilib_LinkedList;

eskilib_LinkedList* eskilib_linkedlist_malloc();

void eskilib_linkedlist_free(eskilib_LinkedList* linkedList);

eskilib_LinkedList_LinkedNode* eskilib_linkedlist_linkednode_malloc(void* value);

enum eskilib_LinkedList_Result eskilib_linkedlist_set_first(eskilib_LinkedList_LinkedNode* nodeToSetFirst, eskilib_LinkedList* linkedList);

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
enum eskilib_LinkedList_Result eskilib_linkedlist_set_last(eskilib_LinkedList_LinkedNode* nodeToSetLast, eskilib_LinkedList* linkedList);

enum eskilib_LinkedList_Result eskilib_linkedlist_set_after(eskilib_LinkedList_LinkedNode* currentNode, eskilib_LinkedList_LinkedNode* nodeToSetAfter);

#endif /* !eskilib_linkedlist_h */

