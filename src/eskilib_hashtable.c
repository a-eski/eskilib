#include <assert.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "eskilib_hashtable.h"
#include "primitives/eskilib_string.h"

#define ESKILIB_HASHTABLE_DEFAULT_SIZE 100
#define ESKILIB_HASHTABLE_SIZE_MULTIPLIER 2

#define ESKILIB_FNV_OFFSET 14695981039346656037UL
#define ESKILIB_FNV_PRIME 1099511628211UL

// fowler noll vo hash function
uint_fast64_t eskilib_hash(char* key) {
	 uint_fast64_t hash = ESKILIB_FNV_OFFSET;
	for (char* p = key; *p; ++p) {
		hash ^= (uint_fast64_t)(unsigned char)(*p);
		hash *= ESKILIB_FNV_PRIME;
	}

	return hash;
}

enum eskilib_HashTable_Result eskilib_hashtable_malloc(const size_t sizeOfHashTable, struct eskilib_HashTable* hashtable) {
	size_t hashTableSize = sizeOfHashTable == 0 ? ESKILIB_HASHTABLE_DEFAULT_SIZE : sizeOfHashTable;

	hashtable->entries = calloc(hashTableSize, sizeof(char));
	if (hashtable->entries == NULL)
		return HT_MALLOC_FAILURE;

	hashtable->size = hashTableSize;
	hashtable->position = 0;

	return HT_SUCCESS;
}

enum eskilib_HashTable_Result eskilib_hashtable_realloc(struct eskilib_HashTable* hashtable) {
	hashtable->size = hashtable->size * ESKILIB_HASHTABLE_SIZE_MULTIPLIER;

	hashtable->entries = realloc(hashtable->entries, hashtable->size * sizeof(struct eskilib_HashTable_Entry));
	if (hashtable->entries == NULL)
		return HT_MALLOC_FAILURE;

	return HT_SUCCESS;
}

void eskilib_hashtable_free(struct eskilib_HashTable* hashtable) {
	assert(hashtable != NULL);
	if (hashtable == NULL)
		return;

	if (hashtable->position > 0) {
		for (size_t i = 0; i < hashtable->size; i++) {
			free((char*)hashtable->entries->key);
			free((char*)hashtable->entries->value);
		}
	}

	free(hashtable->entries);
	hashtable->entries = NULL;
}

const char* eskilib_hashtable_add(char* key, char* value, struct eskilib_HashTable* hashtable) {
	assert(hashtable != NULL);
	assert(value != NULL);
	assert(key != NULL);

	if (hashtable->position >= hashtable->size / ESKILIB_HASHTABLE_SIZE_MULTIPLIER) {
		if (eskilib_hashtable_realloc(hashtable) != HT_SUCCESS)
			return NULL;
	}

	uint_fast64_t hash = eskilib_hash(key);
	size_t index = (size_t)(hash & (uint_fast64_t)(hashtable->size - 1));

	while (hashtable->entries[index].key != NULL) {
		if (hashtable->entries[index].key != NULL && eskilib_string_equals((char*)key, (char*)hashtable->entries[index].key, 255)) {
			hashtable->entries[index].value = value;
			return hashtable->entries->key;
		}

		++index;
		if (index >= hashtable->size)
			index = 0;
	}

	key = strdup(key);
	if (key == NULL) {
		return NULL;
	}

	hashtable->position++;
	hashtable->entries->key = key;
	hashtable->entries->value = value;
	return key;
}

enum eskilib_HashTable_Result eskilib_hashtable_remove(char* key, struct eskilib_HashTable* hashtable) {
	assert(hashtable != NULL);
	if (hashtable == NULL)
		return HT_FAILURE_NULL_REFERENCE;

	assert(key != 0);
	if (key == 0)
		return HT_FAILURE_ZERO_KEY_VALUE;

	return HT_FAILURE;
}

struct eskilib_HashTable_Entry* eskilib_hashtable_get(char* key, struct eskilib_HashTable* hashtable) {
	assert(hashtable != NULL);
	if (hashtable == NULL)
		return NULL;

	assert(key != NULL);
	if (key == NULL)
		return NULL;

	uint_fast64_t hash = eskilib_hash(key);
	size_t index = (size_t)(hash & (uint_fast64_t)(hashtable->size - 1));

	while (hashtable->entries[index].key != NULL) {
		if (eskilib_string_equals((char*)key, (char*)hashtable->entries[index].key, hashtable->entries[index].key_length))
			return &hashtable->entries[index];

		++index;
		if (index >= hashtable->size)
			index = 0;
	}

	return NULL;
}

