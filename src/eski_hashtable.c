// Copyright (c) eski by Alex Eski 2024

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "eski_hashtable.h"

bool eski_hashtable_malloc(struct eski_HashTable* table) {
    table->length = 0;
    table->capacity = eski_HASHTABLE_DEFAULT_CAPACITY;

    table->entries = calloc(table->capacity, sizeof(struct eski_HashTable_Entry));
    if (table->entries == NULL) {
        return false;
    }
    return true;
}

void eski_hashtable_free(struct eski_HashTable* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        free((char*)table->entries[i].key);
    }

    free(table->entries);
}

#define eski_FNV_OFFSET 14695981039346656037UL
#define eski_FNV_PRIME 1099511628211UL

// 64-bit FNV-1a hash
uint64_t eski_hashtable_key(const char* key) {
    uint64_t hash = eski_FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= eski_FNV_PRIME;
    }

    return hash;
}

struct eski_String eski_hashtable_get(const char* key, struct eski_HashTable* table) {
    uint64_t hash = eski_hashtable_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }

        index++; //linear probing
        if (index >= table->capacity) {
            index = 0; //at end of ht, wrap around
        }
    }

    return (struct eski_String){ .value = NULL, .length = 0 };
}

const char* eski_hashtable_set_entry(struct eski_HashTable_Entry* entries, size_t capacity, const char* key, struct eski_String value, size_t* plength) {
    uint64_t hash = eski_hashtable_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }

        index++; //linear probing
        if (index >= capacity) {
            index = 0; // at end of ht, wrap around
        }
    }

    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plength)++;
    }

    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}

bool eski_hashtable_expand(struct eski_HashTable* table) {
    size_t new_capacity = table->capacity * 2;
    if (new_capacity < table->capacity) {
        return false;
    }

    struct eski_HashTable_Entry* new_entries = calloc(new_capacity, sizeof(struct eski_HashTable_Entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < table->capacity; i++) {
        struct eski_HashTable_Entry entry = table->entries[i];
        if (entry.key != NULL) {
            eski_hashtable_set_entry(new_entries, new_capacity, entry.key,
                         entry.value, NULL);
        }
    }

    free(table->entries);
    table->entries = new_entries;
    table->capacity = new_capacity;
    return true;
}

const char* eski_hashtable_set(const char* key, struct eski_String value, struct eski_HashTable* table) {
    assert(value.value != NULL && value.length > 0);
    if (value.value == NULL || value.length == 0) {
        return NULL;
    }

    if (table->length >= table->capacity / 2) {
        if (!eski_hashtable_expand(table)) {
            return NULL;
        }
    }

    return eski_hashtable_set_entry(table->entries, table->capacity, key, value,
                        &table->length);
}
