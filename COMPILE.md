# COMPILE.md

These are just notes from when I was getting back into C programming and learning about GCC, clang, and developing with C on Windows using MSYS2. Also includes useful compiler options found during my research.

## COMPILER OPTIONS

Note: fsanitize not supported on windows: must use WSL2 to use address sanitizer and check for undefined behavior.

Check out these options and research these options more:

-Wall -Wextra -Werror -Wabi -Wformat=2
-mmitigate-rop -Wstack-protector -fstack-protector-strong -fstack-clash-protection -pie -fPIE -D_FORTIFY_SOURCE=2 -Wl,-z,rel -Wl,dynamicbase -Wl,nxcompat
-Wstrict-overflow -fno-strict-overflow -fwrapv -Wstrict-overflow=3

### DEBUG SYMBOLS

-g

### LINKING

-lc (link c stdlib)
-L/usr/lib -lc (link c stdlib using path)

## IDEAS

### TODOS

Rope,Vector,Tree,Set,Arena Allocator,Search Algorithms,Sorting Algorithms

### IMPROVE

Improve stack tests, improve list tests, rework linked list, improve emap tests

## RUN ALL TESTS

### Windows(MSYS2 MinGW GCC)

gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -Detest_ALL *.c -o bin/etests
gcc -std=c2x -Wall -pedantic-errors -Wformat=2 -Wshadow -Detest_ALL -DNDEBUG *.c tests/*.c -o bin/etests
gcc -std=c2x -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion -Wformat=2 -Wshadow -Wvla -fstack-protector-all -Detest_ALL -DNDEBUG src/*.c src/tests/*.c -o bin/etests

gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -Detest_ALL etests.c ellist_tests.c equeue_tests.c estack_tests.c etests.c emap_tests.c edllist_tests.c etest.c ellist.c equeue.c estack.c eda.c emap.c edllist.c -o bin/etests

### Linux(GCC)

gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL *.c -o bin/etests
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL -g *.c -o bin/etests
gcc -std=c2x -Wall -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL -DNDEBUG *.c -o bin/etests
gcc -std=c2x -Wall -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL -DNDEBUG -g *.c -o bin/etests

gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL etests.c ellist_tests.c equeue_tests.c estack_tests.c etests.c emap_tests.c edllist_tests.c tests/estr_tests.c tests/etrie_tests.c etest.c ellist.c equeue.c estack.c eda.c emap.c edllist.c estr.c etrie.c -o bin/etests

valgrind --leak-check=yes ./bin/etests
clang -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined -Detest_ALL *.c -o bin/etests


## COMPILING

### HashTable

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 emap_tests.c etest.c emap.c -o bin/emap_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined emap_tests.c etest.c emap.c estr.c -o bin/emap_tests


gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined emap_tests.c etest.c emap.c estr.c -o bin/emap_tests

### DoublyLinkedList(WIP)

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 edllist_tests.c etest.c edllist.c -o bin/edllist_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined edllist_tests.c etest.c edllist.c -o bin/edllist_tests

### Queue

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 equeue_tests.c etest.c equeue.c -o bin/equeue_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined equeue_tests.c etest.c equeue.c -o bin/equeue_tests

### DA (dynamic array implementation)

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 etests.c etest.c eda.c -o bin/eda_tests
gcc -std=c2x -Wall -pedantic-errors -Wformat=2 etests.c etest.c -DNDEBUG eda.c -o bin/eda_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined etests.c etest.c eda.c -o bin/eda_tests
gcc -std=c2x -Wall -pedantic-errors -Wformat=2 -fsanitize=address,undefined -DNDEBUG etests.c etest.c eda.c -o bin/eda_tests

### LinkedList (singly linked list implementation)

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 ellist_tests.c etest.c ellist.c -o bin/ellist_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined ellist_tests.c etest.c ellist.c -o bin/ellist_tests

### Stack

/*Windows*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 estack_tests.c etest.c estack.c -o bin/estack_tests
/*Windows (Release)*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 estack_tests.c etest.c estack.c -o bin/estack_tests
/*Linux*/
gcc -std=c2x -Wall -Wextra -Werror -pedantic-errors -Wformat=2 -fsanitize=address,undefined estack_tests.c etest.c estack.c -o bin/estack_tests
