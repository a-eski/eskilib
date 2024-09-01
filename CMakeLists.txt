cmake_minimum_required(VERSION 3.29.3)

project(eskilib_tests VERSION 0.0.1)

set(CMAKE_VERBOSE_MAKEFILE off)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(config)

add_subdirectory(src)

