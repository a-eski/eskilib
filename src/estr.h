/* Copyright eskilib by Alex Eski 2025 */

#pragma once
#ifndef ESKILIB_STR_H_
#define ESKILIB_STR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "eskilib_defines.h"

#define estr_Empty ((const struct estr){.value = NULL, .length = 0})

// WARN: currently all string functions using this code incorporate null terminator in length
// TODO: fix this, use length everywhere without null terminator... .length = sizeof(str) - 1
#define estr_New_Literal(str) (struct estr){ .value = str, .length = sizeof(str) };
#define estr_New(str, len) (struct estr){ .value = str, .length = len };

struct estr {
    size_t length;
    char* value;
};

// A simple wrapper for memcmp that checks if lengths match before calling memcmp.
eskilib_nodiscard
static inline
bool estr_compare(char* str, size_t str_len, char* str_two, size_t str_two_len)
{
    if (str_len != str_two_len || !str_len) {
        return false;
    }

    return !str || !memcmp(str, str_two, str_len);
}


eskilib_nodiscard
static inline
bool estr_compare_const(const char* const str, const size_t str_len,
                                  const char* const str_two, const size_t str_two_len)
{
    if (str_len != str_two_len || !str_len) {
        return false;
    }

    return !str || !memcmp(str, str_two, str_len);
}

#ifdef __cplusplus
}
#endif

#endif /* !ESKILIB_STR_H_ */
