/* Copyright (C) eskilib by Alex Eski 2024 */

#include "tests/eskilib_stack_tests.h"
#include "tests/eskilib_linkedlist_tests.h"
#include "tests/eskilib_queue_tests.h"
#include "tests/eskilib_list_tests.h"
#include "tests/emap_tests.h"
#include "tests/eskilib_doublylinkedlist_tests.h"
#include "tests/estr_tests.h"
#include "tests/eskilib_trie_tests.h"

int main(void)
{
    eskilib_stack_tests();

    eskilib_linkedlist_tests();

    eskilib_queue_tests();

    eskilib_list_tests();

    emap_tests();

    eskilib_doublylinkedlist_tests();

    estr_tests();

    eskilib_trie_tests();

    return 0;
}
