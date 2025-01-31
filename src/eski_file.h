// Copyright (c) eski by Alex Eski 2024

#ifndef eski_file_h
#define eski_file_h

#include <stddef.h>
#include <stdio.h>

int eski_fgets(char *input_buffer, size_t size_of_input_buffer, FILE *file_pointer);

int eski_fgets_delimited(char *input_buffer, size_t size_of_input_buffer, FILE *file_pointer,
                                     char delimiter);

#endif // eski_file_h
