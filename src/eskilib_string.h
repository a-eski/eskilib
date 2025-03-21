/* Copyright eskilib (c) by Alex Eski 2024 */

#ifndef ESKILIB_STRING_H_
#define ESKILIB_STRING_H_

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "eskilib_defines.h"

#define eskilib_String_Empty ((const struct eskilib_String){.value = NULL, .length = 0})

// WARN: currently all string functions using this code incorporate null terminator in length
// TODO: fix this, use length everywhere without null terminator... .length = sizeof(str) - 1
#define eskilib_String_New(str) (struct eskilib_String){ .value = str, .length = sizeof(str) };

struct eskilib_String {
    size_t length;
    char* value;
};

// A simple wrapper for memcmp that checks if lengths match before calling memcmp.
eskilib_nodiscard
static inline
bool eskilib_string_compare(char* str, size_t str_len, char* str_two, size_t str_two_len)
{
    if (str_len != str_two_len) {
        return false;
    }

    return !str_len || !memcmp(str, str_two, str_len);
}

eskilib_nodiscard
static inline
bool eskilib_string_compare_const(const char* const str, const size_t str_len,
                                  const char* const str_two, const size_t str_two_len)
{
    if (str_len != str_two_len) {
        return false;
    }

    return !str_len || !memcmp(str, str_two, str_len);
}

bool eskilib_string_contains(const char* string, size_t string_length, const char* string_two,
                             size_t string_two_length);

#endif // !ESKILIB_STRING_H_
