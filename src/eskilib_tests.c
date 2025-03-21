/* Copyright (c) eskilib by Alex Eski 2024 */

#include "tests/eskilib_stack_tests.h"
#include "tests/eskilib_linkedlist_tests.h"
#include "tests/eskilib_queue_tests.h"
#include "tests/eskilib_list_tests.h"
#include "tests/eskilib_hashtable_tests.h"
#include "tests/eskilib_doublylinkedlist_tests.h"
#include "tests/eskilib_string_tests.h"
#include "tests/eskilib_trie_tests.h"

int main(void)
{
	eskilib_stack_tests();

	eskilib_linkedlist_tests();

	eskilib_queue_tests();

	eskilib_list_tests();

	eskilib_hashtable_tests();

	eskilib_doublylinkedlist_tests();

	eskilib_string_tests();

	eskilib_trie_tests();

	return 0;
}

