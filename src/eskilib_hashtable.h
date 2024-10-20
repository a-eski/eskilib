#ifndef eskilib_hashtable_h
#define eskilib_hashtable_h

#include <stdint.h>
#include <stdlib.h>

#include "./primitives/eskilib_string.h"

enum eskilib_HashTable_Result
{
	HT_FAILURE_ZERO_KEY_VALUE = -4,
	HT_FAILURE_OVERFLOW_PROTECTION = -3,
	HT_MALLOC_FAILURE = -2,
	HT_FAILURE_NULL_REFERENCE = -1,
	HT_FAILURE = 0,
	HT_SUCCESS = 1
};

struct eskilib_HashTable_Entry
{
	const char* key;
	uint_fast32_t key_length;
	const char* value;
	uint_fast32_t value_length;
};

struct eskilib_HashTable
{
	size_t size;
	size_t position;
	struct eskilib_HashTable_Entry* entries;
};

enum eskilib_HashTable_Result eskilib_hashtable_malloc(const size_t sizeOfHashTable, struct eskilib_HashTable* hashtable);

void eskilib_hashtable_free(struct eskilib_HashTable* hashtable);

const char* eskilib_hashtable_add(char* key, char* value, struct eskilib_HashTable* hashtable);

enum eskilib_HashTable_Result eskilib_hashtable_remove(char* key, struct eskilib_HashTable* hashtable);

struct eskilib_HashTable_Entry* eskilib_hashtable_get(char* key, struct eskilib_HashTable* hashtable);

#endif /* !eskilib_hashtable_h */

