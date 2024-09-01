#ifndef eskilib_hashtable_h
#define eskilib_hashtable_h

enum eskilib_HashTable_Result
{
	FAILURE_ZERO_KEY_VALUE = -4,
	FAILURE_OVERFLOW_PROTECTION = -3,
	FAILURE_NULL_ENTRY = -2,
	FAILURE_NULL_HASHTABLE = -1,
	FAILURE = 0,
	SUCCESS = 1
};

typedef struct
{
	size_t key;
	void* value;
} eskilib_HashTable_Entry;

typedef struct
{
	size_t size;
	size_t position;
	eskilib_HashTable_Entry* entries;
} eskilib_HashTable;

eskilib_HashTable* eskilib_hashtable_allocate(const size_t sizeOfHashTable, const size_t sizeOfValues);

void eskilib_hashtable_free(eskilib_HashTable* hashtable);

size_t eskilib_hashtable_add(void* value, eskilib_HashTable* hashtable);

enum eskilib_HashTable_Result eskilib_hashtable_remove(const size_t key, eskilib_HashTable* hashtable);

eskilib_HashTable_Entry* eskilib_hashtable_get(const size_t key, eskilib_HashTable* hashtable);

#endif /* !eskilib_hashtable_h */

