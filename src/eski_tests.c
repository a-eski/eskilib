#include "tests/eski_stack_tests.h"
#include "tests/eski_linkedlist_tests.h"
#include "tests/eski_queue_tests.h"
#include "tests/eski_list_tests.h"
#include "tests/eski_hashtable_tests.h"
#include "tests/eski_doublylinkedlist_tests.h"
#include "tests/eski_string_tests.h"
#include "tests/eski_trie_tests.h"

int main(void)
{
	eski_stack_tests();

	eski_linkedlist_tests();

	eski_queue_tests();

	eski_list_tests();

	eski_hashtable_tests();

	eski_doublylinkedlist_tests();

	eski_string_tests();

	eski_trie_tests();

	return 0;
}

