/* Copyright (C) eskilib by Alex Eski 2024 */

#ifndef ellist_H_
#define ellist_H_

#ifdef __cplusplus
extern "C" {
#endif

enum ellist_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct ellist_LinkedNode_of_void_star
{
	void* value;
	struct ellist_LinkedNode_of_void_star* next;
} ellist_Node;

typedef struct
{
	ellist_Node* first;
} ellist;

ellist* ellist_malloc(void);

void ellist_free(ellist* llist);

ellist_Node* ellist_linkednode_malloc(void* value);

enum ellist_Result ellist_set_first(ellist_Node* nodeToSetFirst, ellist* llist);

/* Not recommended for use unless you have a really good reason, as it has to traverse the entire list to get to the end. */
enum ellist_Result ellist_set_last(ellist_Node* nodeToSetLast, ellist* llist);

enum ellist_Result ellist_set_after(ellist_Node* currentNode, ellist_Node* nodeToSetAfter);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* !ellist_H_ */
