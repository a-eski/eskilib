/* Copyright eski by Alex Eski 2024 */

#ifndef eski_string_h
#define eski_string_h

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define eski_String_Empty ((const struct eski_String){.value = NULL, .length = 0})

struct eski_String
{
    size_t length;
    char *value;
};

char *eski_string_copy(char *dest, char *source, const size_t maxStringSize);

// checks if two strings are equivalent and returns true if they are, false otherwise.
bool eski_string_equals(char *stringOne, char *stringTwo, const size_t maxStringSize);

// returns values similar to strcmp from string.h, return value == 0 if strings match.
int_fast32_t eski_string_compare(char *stringOne, char *stringTwo, const size_t maxStringSize);

bool eski_string_contains_unsafe(const char *string, const char *substring);
bool eski_string_contains(const struct eski_String string, const struct eski_String substring);
bool eski_string_contains_s(const char *string, size_t string_length, const struct eski_String substring);
bool eski_string_contains_s2(const char *string, size_t string_length, const char *string_two,
                                size_t string_two_length);

#endif // !eski_string_h
