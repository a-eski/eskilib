// Copyright (c) eski by Alex Eski 2024

#ifndef eski_hashtable_h
#define eski_hashtable_h

#include <stdbool.h>
#include <stddef.h>

#include "eski_string.h"

#define eski_HASHTABLE_DEFAULT_CAPACITY 100

struct eski_HashTable_Entry {
    const char* key;
    struct eski_String value;
};

struct eski_HashTable {
    size_t capacity;
    size_t length;
    struct eski_HashTable_Entry* entries;
};

bool eski_hashtable_malloc(struct eski_HashTable* table);

void eski_hashtable_free(struct eski_HashTable* table);

struct eski_String eski_hashtable_get(const char* key, struct eski_HashTable* table);

const char* eski_hashtable_set(const char* key, struct eski_String value, struct eski_HashTable* table);

#endif // eski_hashtable_h
