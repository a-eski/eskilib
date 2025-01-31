// Copyright (c) eski by Alex Eski 2024

#include "eski_defines.h"
#include "eski_file.h"

// simple fgets implementation that returns the number of characters read
eski_nodiscard int eski_fgets(char *input_buffer, size_t size_of_input_buffer, FILE *file_pointer)
{
    register int character;
    register char *buffer = input_buffer;
    int characters_read = 0;

    while (--size_of_input_buffer > 0 && (character = getc(file_pointer)) != EOF)
    {
        ++characters_read;

        if ((*buffer = (char)character) == '\n')
            break;
        else
            ++buffer;
    }

    *buffer = '\0';
    return characters_read;
}

eski_nodiscard int eski_fgets_delimited(char *input_buffer, size_t size_of_input_buffer,
                                                       FILE *file_pointer, char delimiter)
{
    register int character;
    register char *buffer = input_buffer;
    int characters_read = 0;

    while (--size_of_input_buffer > 0 && (character = getc(file_pointer)) != EOF)
    {
        ++characters_read;

        if ((*buffer = (char)character) == delimiter)
            break;
        else
            ++buffer;
    }

    *buffer = '\0';
    return characters_read;
}
