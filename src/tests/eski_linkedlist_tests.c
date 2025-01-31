#include <stdio.h>
#include <stdlib.h>
#include "../eski_test.h"
#include "../eski_linkedlist.h"

void eski_linkedlist_malloc_test(void)
{
	eski_LinkedList* linkedList = NULL;

	linkedList = eski_linkedlist_malloc();

	eski_assert(linkedList != NULL);
	eski_assert(linkedList->first == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_linkednode_malloc_test(void)
{
	eski_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	node = eski_linkedlist_linkednode_malloc(&value);

	eski_assert(node != NULL);
	eski_assert(value == *(size_t*)node->value);
	eski_assert(node->next == NULL);

	free(node);
}

void eski_linkedlist_set_first_on_empty_linkedlist_test(void)
{
	eski_LinkedList* linkedList = NULL;
	eski_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eski_LinkedList_Result setFirstResult = FAILURE;

	linkedList = eski_linkedlist_malloc();
	node = eski_linkedlist_linkednode_malloc(&value);

	setFirstResult = eski_linkedlist_set_first(node, linkedList);

	eski_assert(setFirstResult == SUCCESS);
	eski_assert(linkedList->first == node);
	eski_assert(linkedList->first->value == node->value);
	eski_assert(linkedList->first->next == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_set_first_on_nonempty_linkedlist_test(void)
{
	eski_LinkedList* linkedList = NULL;
	eski_LinkedList_LinkedNode* node = NULL;
	eski_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eski_LinkedList_Result setFirstResultOne = FAILURE;
	enum eski_LinkedList_Result setFirstResultTwo = FAILURE;

	linkedList = eski_linkedlist_malloc();
	node = eski_linkedlist_linkednode_malloc(&valueOne);
	nextNode = eski_linkedlist_linkednode_malloc(&valueTwo);

	setFirstResultOne = eski_linkedlist_set_first(node, linkedList);
	setFirstResultTwo = eski_linkedlist_set_first(nextNode, linkedList);

	eski_assert(setFirstResultOne == SUCCESS);
	eski_assert(setFirstResultTwo == SUCCESS);
	eski_assert(linkedList->first == nextNode);
	eski_assert(linkedList->first->value == nextNode->value);
	eski_assert(linkedList->first->next == node);
	eski_assert(linkedList->first->next->value == node->value);
	eski_assert(linkedList->first->next->next == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_set_last_on_empty_linkedlist_test(void)
{
	eski_LinkedList* linkedList = NULL;
	eski_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;
	enum eski_LinkedList_Result setLastResult = FAILURE;

	linkedList = eski_linkedlist_malloc();
	node = eski_linkedlist_linkednode_malloc(&value);

	setLastResult = eski_linkedlist_set_last(node, linkedList);

	eski_assert(setLastResult == SUCCESS);
	eski_assert(value == *(size_t*)linkedList->first->value);
	eski_assert(linkedList->first->next == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_set_last_on_nonempty_linkedlist_test(void)
{
	eski_LinkedList* linkedList = NULL;
	eski_LinkedList_LinkedNode* node = NULL;
	eski_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	enum eski_LinkedList_Result setLastResultOne = FAILURE;
	enum eski_LinkedList_Result setLastResultTwo = FAILURE;

	linkedList = eski_linkedlist_malloc();
	node = eski_linkedlist_linkednode_malloc(&valueOne);
	nextNode = eski_linkedlist_linkednode_malloc(&valueTwo);

	setLastResultOne = eski_linkedlist_set_last(node, linkedList);
	setLastResultTwo = eski_linkedlist_set_last(nextNode, linkedList);

	eski_assert(setLastResultOne == SUCCESS);
	eski_assert(setLastResultTwo == SUCCESS);
	eski_assert(linkedList->first == node);
	eski_assert(valueOne == *(size_t*)linkedList->first->value);
	eski_assert(linkedList->first->next == nextNode);
	eski_assert(valueTwo == *(size_t*)linkedList->first->next->value);
	eski_assert(linkedList->first->next->next == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_set_after_test(void)
{
	eski_LinkedList* linkedList = NULL;
	eski_LinkedList_LinkedNode* node = NULL;
	eski_LinkedList_LinkedNode* secondNode = NULL;
	eski_LinkedList_LinkedNode* thirdNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;
	enum eski_LinkedList_Result setFirstResult = FAILURE;
	enum eski_LinkedList_Result setLastResult = FAILURE;
	enum eski_LinkedList_Result setAfterResult = FAILURE;

	linkedList = eski_linkedlist_malloc();
	node = eski_linkedlist_linkednode_malloc(&valueOne);
	secondNode = eski_linkedlist_linkednode_malloc(&valueTwo);
	thirdNode = eski_linkedlist_linkednode_malloc(&valueThree);

	setFirstResult = eski_linkedlist_set_first(node, linkedList);
	setLastResult = eski_linkedlist_set_last(secondNode, linkedList);

	setAfterResult = eski_linkedlist_set_after(linkedList->first, thirdNode);

	eski_assert(setFirstResult == SUCCESS);
	eski_assert(setLastResult == SUCCESS);
	eski_assert(setAfterResult == SUCCESS);
	eski_assert(linkedList->first == node);
	eski_assert(valueOne == *(size_t*)linkedList->first->value);
	eski_assert(linkedList->first->next == thirdNode);
	eski_assert(valueThree == *(size_t*)linkedList->first->next->value);
	eski_assert(linkedList->first->next->next == secondNode);
	eski_assert(linkedList->first->next->next->value);
	eski_assert(linkedList->first->next->next->next == NULL);

	eski_linkedlist_free(linkedList);
}

void eski_linkedlist_release_tests(void)
{
}

void eski_linkedlist_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_linkedlist_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_linkedlist_malloc_test", eski_linkedlist_malloc_test);

	eski_test_run("eski_linkedlist_linkednode_malloc_test", eski_linkedlist_linkednode_malloc_test);

	eski_test_run("eski_linkedlist_set_first_on_empty_linkedlist_test", eski_linkedlist_set_first_on_empty_linkedlist_test);

	eski_test_run("eski_linkedlist_set_first_on_nonempty_linkedlist_test", eski_linkedlist_set_first_on_nonempty_linkedlist_test);

	eski_test_run("eski_linkedlist_set_last_on_empty_linkedlist_test", eski_linkedlist_set_last_on_empty_linkedlist_test);

	eski_test_run("eski_linkedlist_set_first_on_nonempty_linkedlist_test", eski_linkedlist_set_first_on_nonempty_linkedlist_test);

	eski_test_run("eski_linkedlist_set_after_test", eski_linkedlist_set_after_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_linkedlist_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
