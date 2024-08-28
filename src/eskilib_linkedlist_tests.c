#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "eskilib_test.h"
#include "eskilib_linkedlist.h"

void eskilib_linkedlist_allocate_test()
{
	eskilib_LinkedList* linkedList = NULL;

	linkedList = eskilib_linkedlist_allocate();

	assert(linkedList != NULL);
	assert(linkedList->First == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_linkednode_allocate_test()
{
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	node = eskilib_linkedlist_linkednode_allocate(&value);

	assert(node != NULL);
	assert(value == *(size_t*)node->Value);
	assert(node->Next == NULL);

	free(node);
}

void eskilib_linkedlist_set_first_on_empty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&value);

	eskilib_linkedlist_set_first(node, linkedList);

	assert(linkedList->First == node);
	assert(linkedList->First->Value == node->Value);
	assert(linkedList->First->Next == NULL);
	
	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_first_on_nonempty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);

	eskilib_linkedlist_set_first(node, linkedList);
	eskilib_linkedlist_set_first(nextNode, linkedList);

	assert(linkedList->First == nextNode);
	assert(linkedList->First->Value == nextNode->Value);
	assert(linkedList->First->Next == node);
	assert(linkedList->First->Next->Value == node->Value);
	assert(linkedList->First->Next->Next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_empty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	size_t value = 1001;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&value);

	eskilib_linkedlist_set_last(node, linkedList);

	assert(value == *(size_t*)linkedList->First->Value);
	assert(linkedList->First->Next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_last_on_nonempty_linkedlist_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* nextNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	nextNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);

	eskilib_linkedlist_set_last(node, linkedList);
	eskilib_linkedlist_set_last(nextNode, linkedList);

	assert(linkedList->First == node);
	assert(valueOne == *(size_t*)linkedList->First->Value);
	assert(linkedList->First->Next == nextNode);
	assert(valueTwo == *(size_t*)linkedList->First->Next->Value);
	assert(linkedList->First->Next->Next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_set_after_test()
{
	eskilib_LinkedList* linkedList = NULL;
	eskilib_LinkedList_LinkedNode* node = NULL;
	eskilib_LinkedList_LinkedNode* secondNode = NULL;
	eskilib_LinkedList_LinkedNode* thirdNode = NULL;
	size_t valueOne = 1001;
	size_t valueTwo = 2002;
	size_t valueThree = 3003;

	linkedList = eskilib_linkedlist_allocate();
	node = eskilib_linkedlist_linkednode_allocate(&valueOne);
	secondNode = eskilib_linkedlist_linkednode_allocate(&valueTwo);
	thirdNode = eskilib_linkedlist_linkednode_allocate(&valueThree);

	eskilib_linkedlist_set_first(node, linkedList);
	eskilib_linkedlist_set_last(secondNode, linkedList);

	eskilib_linkedlist_set_after(linkedList->First, thirdNode);
	assert(linkedList->First == node);
	assert(valueOne == *(size_t*)linkedList->First->Value);
	assert(linkedList->First->Next == thirdNode);
	assert(valueThree == *(size_t*)linkedList->First->Next->Value);
	assert(linkedList->First->Next->Next == secondNode);
	assert(linkedList->First->Next->Next->Value);
	assert(linkedList->First->Next->Next->Next == NULL);

	eskilib_linkedlist_free(linkedList);
}

void eskilib_linkedlist_tests()
{
	eskilib_test_run("eskilib_linkedlist_allocate_test", eskilib_linkedlist_allocate_test);

	eskilib_test_run("eskilib_linkedlist_linkednode_allocate_test", eskilib_linkedlist_linkednode_allocate_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_empty_linkedlist_test", eskilib_linkedlist_set_first_on_empty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_nonempty_linkedlist_test", eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_last_on_empty_linkedlist_test", eskilib_linkedlist_set_last_on_empty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_first_on_nonempty_linkedlist_test", eskilib_linkedlist_set_first_on_nonempty_linkedlist_test);

	eskilib_test_run("eskilib_linkedlist_set_after_test", eskilib_linkedlist_set_after_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_linkedlist_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
