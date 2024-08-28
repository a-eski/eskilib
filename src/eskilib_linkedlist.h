#ifndef eskilib_linkedlist_h
#define eskilib_linkedlist_h

#include <stdbool.h>

typedef struct eskilib_LinkedList_LinkedNode_of_void_star
{
	void* Value;
	struct eskilib_LinkedList_LinkedNode_of_void_star* Next;
} eskilib_LinkedList_LinkedNode;

typedef struct
{
	eskilib_LinkedList_LinkedNode* First;
} eskilib_LinkedList;

eskilib_LinkedList* eskilib_linkedlist_allocate();

void eskilib_linkedlist_free(eskilib_LinkedList* linkedList);

eskilib_LinkedList_LinkedNode* eskilib_linkedlist_linkednode_allocate(void* value);

bool eskilib_linkedlist_set_first(eskilib_LinkedList_LinkedNode* nodeToSetFirst, eskilib_LinkedList* linkedList);

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
bool eskilib_linkedlist_set_last(eskilib_LinkedList_LinkedNode* nodeToSetLast, eskilib_LinkedList* linkedList);

bool eskilib_linkedlist_set_after(eskilib_LinkedList_LinkedNode* currentNode, eskilib_LinkedList_LinkedNode* nodeToSetAfter);

#endif /* !eskilib_linkedlist_h */

