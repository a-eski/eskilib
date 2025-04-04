#ifndef ESKILIB_EDLLIST_H_
#define ESKILIB_EDLLIST_H_

#ifdef __cplusplus
extern "C" {
#endif

enum edllist_Result
{
	FAILURE_ALREADY_LINKED_NODE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_NODE = -2,
	FAILURE_NULL_LINKEDLIST = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct edllist_LinkedNode_of_void_star
{
	void* value;
	struct edllist_LinkedNode_of_void_star* next;
	struct edllist_LinkedNode_of_void_star* previous;
} edllist_LinkedNode;

typedef struct
{
	edllist_LinkedNode* first;
	edllist_LinkedNode* last;
} edllist;

edllist* edllist_malloc(void);

void edllist_free(edllist* linkedList);

edllist_LinkedNode* edllist_linkednode_malloc(void* value);

enum edllist_Result edllist_set_first(edllist_LinkedNode* nodeToSetFirst, edllist* linkedList);

enum edllist_Result edllist_set_last(edllist_LinkedNode* nodeToSetLast, edllist* linkedList);

enum edllist_Result edllist_set_after(edllist_LinkedNode* currentNode,
					edllist_LinkedNode* nodeToSetAfter,
					edllist* linkedList);

/*
enum edllist_Result edllist_set_before(edllist_LinkedNode* currentNode, edllist_LinkedNode* nodeToSetBefore);
*/

#ifdef __cplusplus
}
#endif // __cplusplus

#endif /* !ESKILIB_EDLLIST_H_ */
