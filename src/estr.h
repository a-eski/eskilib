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

#define estr_Empty ((const struct estr){.val = NULL, .len = 0})

// WARN: currently all string functions using this code incorporate null terminator in len
// TODO: fix this, use len everywhere without null terminator... .len = sizeof(str) - 1
#define estr_New_Literal(str) (struct estr){ .val = str, .len = sizeof(str) };
#define estr_New(str, str_len) (struct estr){ .val = str, .len = str_len };

struct estr {
    size_t len;
    char* val;
};

typedef struct estr estr;

// A simple wrapper for memcmp that checks if lens match before calling memcmp.
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
