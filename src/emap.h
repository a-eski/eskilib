/* Copyright (c) eskilib by Alex Eski 2025 */

#ifndef ESKILIB_EMAP_H_
#define ESKILIB_EMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stddef.h>

#include "estr.h"

#define EMAP_DEFAULT_CAPACITY 100

struct emap_Entry {
    const char* key;
    estr value;
};
typedef struct emap_Entry emap_Entry;

struct emap {
    size_t size;
    size_t capacity;
    struct emap_Entry* entries;
};
typedef struct emap emap;

bool emap_malloc(emap* table);

void emap_free(emap* hmap);

estr emap_get(const char* key, emap* hmap);

bool emap_exists(const char* key, emap* hmap);

const char* emap_set(const char* key, estr value, emap* hmap);

#ifdef __cplusplus
}
#endif

#endif // ESKILIB_EMAP_H_
