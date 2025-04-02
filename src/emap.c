/* Copyright (c) eskilib by Alex Eski 2025 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "emap.h"
#include "estr.h"

bool emap_malloc(struct emap* hmap)
{
    hmap->size = 0;
    hmap->capacity = EMAP_DEFAULT_CAPACITY;

    hmap->entries = calloc(hmap->capacity, sizeof(struct emap_Entry));
    if (hmap->entries == NULL) {
        return false;
    }
    return true;
}

void emap_free(struct emap* hmap)
{
    for (size_t i = 0; i < hmap->capacity; i++) {
        if (hmap->entries[i].key)
            free((char*)hmap->entries[i].key);
    }

    free(hmap->entries);
}

#define ESKILIB_FNV_OFFSET 14695981039346656037UL
#define ESKILIB_FNV_PRIME 1099511628211UL

// 64-bit FNV-1a hash
uint64_t emap_key(const char* key)
{
    uint64_t hash = ESKILIB_FNV_OFFSET;
    for (const char* p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= ESKILIB_FNV_PRIME;
    }

    return hash;
}

struct estr emap_get(const char* key, struct emap* hmap)
{
    uint64_t hash = emap_key(key);
    size_t index = (size_t)(hash & (uint64_t)(hmap->capacity - 1));

    while (hmap->entries[index].key != NULL) {
        if (strcmp(key, hmap->entries[index].key) == 0) {
            return hmap->entries[index].value;
        }

        index++; // linear probing
        if (index >= hmap->capacity) {
            index = 0; // at end of ht, wrap around
        }
    }

    return estr_Empty;
}

bool emap_exists(const char* key, struct emap* hmap)
{
    uint64_t hash = emap_key(key);
    size_t index = (size_t)(hash & (uint64_t)(hmap->capacity - 1));

    while (hmap->entries[index].key != NULL) {
        if (strcmp(key, hmap->entries[index].key) == 0) {
            return true;
        }

        index++; // linear probing
        if (index >= hmap->capacity) {
            index = 0; // at end of ht, wrap around
        }
    }

    return false;
}

const char* emap_set_entry(struct emap_Entry* entries, size_t capacity, const char* key,
                                        struct estr value, size_t* plen)
{
    uint64_t hash = emap_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

    while (entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }

        index++; // linear probing
        if (index >= capacity) {
            index = 0; // at end of ht, wrap around
        }
    }

    if (plen != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }
        (*plen)++;
    }

    entries[index].key = (char*)key;
    entries[index].value = value;
    return key;
}

bool emap_expand(struct emap* hmap)
{
    size_t new_capacity = hmap->capacity * 2;
    if (new_capacity < hmap->capacity) {
        return false;
    }

    struct emap_Entry* new_entries = calloc(new_capacity, sizeof(struct emap_Entry));
    if (new_entries == NULL) {
        return false;
    }

    // Iterate entries, move all non-empty ones to new table's entries.
    for (size_t i = 0; i < hmap->capacity; i++) {
        struct emap_Entry entry = hmap->entries[i];
        if (entry.key != NULL) {
            emap_set_entry(new_entries, new_capacity, entry.key, entry.value, NULL);
        }
    }

    free(hmap->entries);
    hmap->entries = new_entries;
    hmap->capacity = new_capacity;
    return true;
}

const char* emap_set(const char* key, struct estr value, struct emap* hmap)
{
    assert(value.val != NULL && value.len > 0);
    if (value.val == NULL || value.len == 0) {
        return NULL;
    }

    if (hmap->size >= hmap->capacity / 2) {
        if (!emap_expand(hmap)) {
            return NULL;
        }
    }

    return emap_set_entry(hmap->entries, hmap->capacity, key, value, &hmap->size);
}
