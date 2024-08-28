#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "eskilib_error_handler.h"
#include "eskilib_hashtable.h"

#define ESKILIB_HASHTABLE_DEFAULT_SIZE 100

eskilib_HashTable* eskilib_hashtable_allocate(const size_t sizeOfHashTable, const size_t sizeOfValues)
{
	eskilib_HashTable* hashtable = NULL;
	size_t hashTableSize = 0;

	assert(sizeOfValues > 0);
	if (sizeOfValues == 0)
	{
		return NULL;
	}

	hashtable = malloc(sizeof(eskilib_HashTable));

	if (hashtable == NULL)
	{
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_ArrayList.\n");
	}

	hashTableSize = sizeOfHashTable == 0 ? ESKILIB_HASHTABLE_DEFAULT_SIZE : sizeOfHashTable;

	hashtable->Entries = malloc(hashTableSize * sizeof(eskilib_HashTable_Entry));

	if (hashtable->Entries == NULL)
	{
		eskilib_output_allocation_error_and_exit("Failed to allocate eskilib_ArrayList->Elements.\n");
	}

	hashtable->Size = hashTableSize;
	hashtable->Position = 0;

	return hashtable;
}

void eskilib_hashtable_free(eskilib_HashTable* hashtable)
{
	assert(hashtable != NULL);
	if (hashtable == NULL)
	{
		return;
	}

	free(hashtable->Entries);
	hashtable->Entries = NULL;
	free(hashtable);
	hashtable = NULL;
}

size_t eskilib_hashtable_add(void* value, eskilib_HashTable* hashtable)
{
	assert(hashtable != NULL);
	if (hashtable)
	{
		return 0;
	}

	assert(value != NULL);
	if (value == NULL)
	{
		return 0;
	}

	return 0;
}

bool eskilib_hashtable_remove(const size_t key, eskilib_HashTable* hashtable)
{
	assert(hashtable != NULL);
	if (hashtable == NULL)
	{
		return false;
	}

	assert(key != 0);
	if (key != 0)
	{
		return false;
	}

	return false;
}

eskilib_HashTable_Entry* eskilib_hashtable_get(const size_t key, eskilib_HashTable* hashtable)
{
	assert(hashtable != NULL);
	if (hashtable == NULL)
	{
		return NULL;
	}

	assert(key != 0);
	if (key == 0)
	{
		return NULL;
	}

	return NULL;
}
