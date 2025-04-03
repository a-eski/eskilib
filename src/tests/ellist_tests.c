#include <stdio.h>
#include <stdlib.h>
#include "../etest.h"
#include "../ellist.h"

void ellist_malloc_test(void)
{
	ellist* llist = NULL;

	llist = ellist_malloc();

	eassert(llist != NULL);
	eassert(llist->first == NULL);

	ellist_free(llist);
}

void ellist_linkednode_malloc_test(void)
{
	ellist_Node* node = NULL;
	size_t value = 1001;

	node = ellist_linkednode_malloc(&value);

	eassert(node != NULL);
	eassert(value == *(size_t*)node->value);
	eassert(node->next == NULL);

	free(node);
}

void ellist_set_first_on_empty_linkedlist_test(void)
{
	ellist* llist = NULL;
	ellist_Node* node = NULL;
	size_t value = 1001;
	enum ellist_Result setFirstResult = FAILURE;

	llist = ellist_malloc();
	node = ellist_linkednode_malloc(&value);

	setFirstResult = ellist_set_first(node, llist);

	eassert(setFirstResult == SUCCESS);
	eassert(llist->first == node);
	eassert(llist->first->value == node->value);
	eassert(llist->first->next == NULL);

	ellist_free(llist);
}

void ellist_set_first_on_nonempty_linkedlist_test(void)
{
	ellist* llist = NULL;
	ellist_Node* node = NULL;
	ellist_Node* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum ellist_Result setFirstResultOne = FAILURE;
	enum ellist_Result setFirstResultTwo = FAILURE;

	llist = ellist_malloc();
	node = ellist_linkednode_malloc(&valueOne);
	nextNode = ellist_linkednode_malloc(&valueTwo);

	setFirstResultOne = ellist_set_first(node, llist);
	setFirstResultTwo = ellist_set_first(nextNode, llist);

	eassert(setFirstResultOne == SUCCESS);
	eassert(setFirstResultTwo == SUCCESS);
	eassert(llist->first == nextNode);
	eassert(llist->first->value == nextNode->value);
	eassert(llist->first->next == node);
	eassert(llist->first->next->value == node->value);
	eassert(llist->first->next->next == NULL);

	ellist_free(llist);
}

void ellist_set_last_on_empty_linkedlist_test(void)
{
	ellist* llist = NULL;
	ellist_Node* node = NULL;
	size_t value = 1001;
	enum ellist_Result setLastResult = FAILURE;

	llist = ellist_malloc();
	node = ellist_linkednode_malloc(&value);

	setLastResult = ellist_set_last(node, llist);

	eassert(setLastResult == SUCCESS);
	eassert(value == *(size_t*)llist->first->value);
	eassert(llist->first->next == NULL);

	ellist_free(llist);
}

void ellist_set_last_on_nonempty_linkedlist_test(void)
{
	ellist* llist = NULL;
	ellist_Node* node = NULL;
	ellist_Node* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum ellist_Result setLastResultOne = FAILURE;
	enum ellist_Result setLastResultTwo = FAILURE;

	llist = ellist_malloc();
	node = ellist_linkednode_malloc(&valueOne);
	nextNode = ellist_linkednode_malloc(&valueTwo);

	setLastResultOne = ellist_set_last(node, llist);
	setLastResultTwo = ellist_set_last(nextNode, llist);

	eassert(setLastResultOne == SUCCESS);
	eassert(setLastResultTwo == SUCCESS);
	eassert(llist->first == node);
	eassert(valueOne == *(size_t*)llist->first->value);
	eassert(llist->first->next == nextNode);
	eassert(valueTwo == *(size_t*)llist->first->next->value);
	eassert(llist->first->next->next == NULL);

	ellist_free(llist);
}

void ellist_set_after_test(void)
{
	ellist* llist = NULL;
	ellist_Node* node = NULL;
	ellist_Node* secondNode = NULL;
	ellist_Node* thirdNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;
	enum ellist_Result setFirstResult = FAILURE;
	enum ellist_Result setLastResult = FAILURE;
	enum ellist_Result setAfterResult = FAILURE;

	llist = ellist_malloc();
	node = ellist_linkednode_malloc(&valueOne);
	secondNode = ellist_linkednode_malloc(&valueTwo);
	thirdNode = ellist_linkednode_malloc(&valueThree);

	setFirstResult = ellist_set_first(node, llist);
	setLastResult = ellist_set_last(secondNode, llist);

	setAfterResult = ellist_set_after(llist->first, thirdNode);

	eassert(setFirstResult == SUCCESS);
	eassert(setLastResult == SUCCESS);
	eassert(setAfterResult == SUCCESS);
	eassert(llist->first == node);
	eassert(valueOne == *(size_t*)llist->first->value);
	eassert(llist->first->next == thirdNode);
	eassert(valueThree == *(size_t*)llist->first->next->value);
	eassert(llist->first->next->next == secondNode);
	eassert(llist->first->next->next->value);
	eassert(llist->first->next->next->next == NULL);

	ellist_free(llist);
}

void ellist_release_tests(void)
{
}

void ellist_tests(void)
{
	etest_start();

	etest_run(ellist_malloc_test);
	etest_run(ellist_linkednode_malloc_test);
	etest_run(ellist_set_first_on_empty_linkedlist_test);
	etest_run(ellist_set_first_on_nonempty_linkedlist_test);
	etest_run(ellist_set_last_on_empty_linkedlist_test);
	etest_run(ellist_set_first_on_nonempty_linkedlist_test);
	etest_run(ellist_set_after_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void)
{
	ellist_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
