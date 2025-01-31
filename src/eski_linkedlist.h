#ifndef eski_linkedlist_h
#define eski_linkedlist_h

enum eski_LinkedList_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct eski_LinkedList_LinkedNode_of_void_star
{
	void* value;
	struct eski_LinkedList_LinkedNode_of_void_star* next;
} eski_LinkedList_LinkedNode;

typedef struct
{
	eski_LinkedList_LinkedNode* first;
} eski_LinkedList;

eski_LinkedList* eski_linkedlist_malloc(void);

void eski_linkedlist_free(eski_LinkedList* linkedList);

eski_LinkedList_LinkedNode* eski_linkedlist_linkednode_malloc(void* value);

enum eski_LinkedList_Result eski_linkedlist_set_first(eski_LinkedList_LinkedNode* nodeToSetFirst, eski_LinkedList* linkedList);

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
enum eski_LinkedList_Result eski_linkedlist_set_last(eski_LinkedList_LinkedNode* nodeToSetLast, eski_LinkedList* linkedList);

enum eski_LinkedList_Result eski_linkedlist_set_after(eski_LinkedList_LinkedNode* currentNode, eski_LinkedList_LinkedNode* nodeToSetAfter);

#endif /* !eski_linkedlist_h */
