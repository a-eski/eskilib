#!/bin/env bash

gcc -std=c2x -Wall -Wextra -Werror -Wpedantic -pedantic-errors -Wconversion -Wsign-conversion -Wformat=2 -Wshadow -Wvla -fstack-protector-all -Detest_ALL -DNDEBUG src/*.c src/tests/*.c -o bin/eskilib_tests
bin/eskilib_tests
