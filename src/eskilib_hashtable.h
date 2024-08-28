#ifndef eskilib_hashtable_h
#define eskilib_hashtable_h

typedef struct
{
	size_t Key;
	void* Value;
} eskilib_HashTable_Entry;

typedef struct
{
	size_t Size;
	size_t Position;
	eskilib_HashTable_Entry* Entries;
} eskilib_HashTable;

eskilib_HashTable* eskilib_hashtable_allocate(const size_t sizeOfHashTable, const size_t sizeOfValues);

void eskilib_hashtable_free(eskilib_HashTable* hashtable);

size_t eskilib_hashtable_add(void* value, eskilib_HashTable* hashtable);

bool eskilib_hashtable_remove(const size_t key, eskilib_HashTable* hashtable);

eskilib_HashTable_Entry* eskilib_hashtable_get(const size_t key, eskilib_HashTable* hashtable);

#endif /* !eskilib_hashtable_h */

