#include <stddef.h>
#include <stdlib.h>
#include "../edllist.h"
#include "../etest.h"

void edllist_malloc_test(void)
{
	edllist* linkedList = edllist_malloc();

	eassert(linkedList != NULL);
	eassert(linkedList->first == NULL);
	eassert(linkedList->last == NULL);

	edllist_free(linkedList);
}

void edllist_set_first_empty_list_test(void)
{

	edllist* linkedList = NULL;
	edllist_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = edllist_malloc();
	node = edllist_linkednode_malloc(&value);

	edllist_set_first(node, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == node);
	eassert(*(size_t*)linkedList->first->value == value);

	eassert(linkedList->last == node);
	eassert(*(size_t*)linkedList->last->value == value);
	eassert(linkedList->last->next == NULL);

	edllist_free(linkedList);
}

void edllist_set_first_nonempty_list_test(void)
{

	edllist* linkedList = NULL;
	edllist_LinkedNode* nodeOne = NULL;
	edllist_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = edllist_malloc();

	nodeOne = edllist_linkednode_malloc(&valueOne);
	nodeTwo = edllist_linkednode_malloc(&valueTwo);

	edllist_set_first(nodeOne, linkedList);
	edllist_set_first(nodeTwo, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == nodeTwo);
	eassert(linkedList->first->next == nodeOne);
	eassert(*(size_t*)linkedList->first->value == valueTwo);

	eassert(linkedList->last->previous == nodeTwo);
	eassert(linkedList->last == nodeOne);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueOne);

	edllist_free(linkedList);
}

void edllist_set_last_empty_list_test(void)
{

	edllist* linkedList = NULL;
	edllist_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = edllist_malloc();
	node = edllist_linkednode_malloc(&value);

	edllist_set_last(node, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == node);
	eassert(*(size_t*)linkedList->first->value == value);

	eassert(linkedList->last == node);
	eassert(*(size_t*)linkedList->last->value == value);
	eassert(linkedList->last->next == NULL);

	edllist_free(linkedList);
}

void edllist_set_last_nonempty_list_test(void)
{
	edllist* linkedList = NULL;
	edllist_LinkedNode* nodeOne = NULL;
	edllist_LinkedNode* nodeTwo = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = edllist_malloc();

	nodeOne = edllist_linkednode_malloc(&valueOne);
	nodeTwo = edllist_linkednode_malloc(&valueTwo);

	edllist_set_last(nodeOne, linkedList);
	edllist_set_last(nodeTwo, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == nodeOne);
	eassert(linkedList->first->next == nodeTwo);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(linkedList->last->previous == nodeOne);
	eassert(linkedList->last == nodeTwo);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueTwo);

	edllist_free(linkedList);
}

void edllist_set_after_single_entry_list_test(void)
{
	edllist* linkedList = NULL;
	edllist_LinkedNode* currentNode = NULL;
	edllist_LinkedNode* nodeToSetAfter = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = edllist_malloc();

	currentNode = edllist_linkednode_malloc(&valueOne);
	nodeToSetAfter = edllist_linkednode_malloc(&valueTwo);

	edllist_set_first(currentNode, linkedList);
	edllist_set_after(currentNode, nodeToSetAfter, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == currentNode);
	eassert(linkedList->first->next == nodeToSetAfter);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(nodeToSetAfter->previous == currentNode);
	eassert(nodeToSetAfter->next == NULL);
	eassert(*(size_t*)nodeToSetAfter->value = valueTwo);

	eassert(linkedList->last->previous == currentNode);
	eassert(linkedList->last == nodeToSetAfter);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueTwo);

	edllist_free(linkedList);
}

void edllist_set_after_in_middle_of_list_test(void)
{
	edllist* linkedList = NULL;
	edllist_LinkedNode* firstNode = NULL;
	edllist_LinkedNode* nodeToSetAfter = NULL;
	edllist_LinkedNode* lastNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;

	linkedList = edllist_malloc();

	firstNode = edllist_linkednode_malloc(&valueOne);
	nodeToSetAfter = edllist_linkednode_malloc(&valueTwo);
	lastNode = edllist_linkednode_malloc(&valueThree);

	edllist_set_first(firstNode, linkedList);
	edllist_set_last(lastNode, linkedList);
	edllist_set_after(firstNode, nodeToSetAfter, linkedList);

	eassert(linkedList->first->previous == NULL);
	eassert(linkedList->first == firstNode);
	eassert(linkedList->first->next == nodeToSetAfter);
	eassert(*(size_t*)linkedList->first->value == valueOne);

	eassert(nodeToSetAfter->previous = firstNode);
	eassert(*(size_t*)nodeToSetAfter->value == valueTwo);
	eassert(nodeToSetAfter->next = lastNode);

	eassert(linkedList->last == lastNode);
	eassert(linkedList->last->previous == nodeToSetAfter);
	eassert(linkedList->last == lastNode);
	eassert(linkedList->last->next == NULL);
	eassert(*(size_t*)linkedList->last->value == valueThree);

	edllist_free(linkedList);
}

void edllist_tests(void)
{
	etest_start();

	etest_run(edllist_malloc_test);
	etest_run(edllist_set_first_empty_list_test);
	etest_run(edllist_set_first_nonempty_list_test);
	etest_run(edllist_set_last_empty_list_test);
	etest_run(edllist_set_last_nonempty_list_test);
	etest_run(edllist_set_after_single_entry_list_test);
	etest_run(edllist_set_after_in_middle_of_list_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	edllist_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
