/* Copyright (C) eskilib by Alex Eski 2024 */

#include "tests/estack_tests.h"
#include "tests/ellist_tests.h"
#include "tests/equeue_tests.h"
#include "tests/eda_tests.h"
#include "tests/emap_tests.h"
#include "tests/edllist_tests.h"
#include "tests/estr_tests.h"
#include "tests/etrie_tests.h"
#include "data_structure_templates/tests/elist_tests.h"

int main(void)
{
    estack_tests();
    ellist_tests();
    equeue_tests();
    eda_tests();
    emap_tests();
    edllist_tests();
    estr_tests();
    etrie_tests();
    elist_tests();

    return 0;
}
