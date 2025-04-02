/* Copyright (C) eskilib by Alex Eski 2025 */

#ifndef ESKILIB_ESTR_H_
#define ESKILIB_ESTR_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "edefs.h"

struct estr {
    size_t len;
    char* val;
};
typedef struct estr estr;

#define estr_Empty ((estr){.val = NULL, .len = 0})

// WARN: currently all string functions using this code incorporate null terminator in len
// TODO: fix this, use len everywhere without null terminator... .len = sizeof(str) - 1
#define estr_New_Literal(str) (estr){ .val = str, .len = sizeof(str) };
#define estr_New(str, str_len) (estr){ .val = str, .len = str_len };

// A simple wrapper for memcmp that checks if lens match before calling memcmp.
enodiscard
static inline
bool estr_compare(char* str, size_t str_len, char* str_two, size_t str_two_len)
{
    if (str_len != str_two_len || !str_len) {
        return false;
    }

    return !str || !memcmp(str, str_two, str_len);
}


enodiscard
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

#endif /* !ESKILIB_ESTR_H_ */
