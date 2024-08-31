#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include "eskilib_hashtable.h"
#include "eskilib_test.h"

void eskilib_hashtable_allocate_default_size_test()
{
	eskilib_HashTable* hashTable = NULL;

	hashTable = eskilib_hashtable_allocate(0, sizeof(size_t*));

	assert(hashTable != NULL);
	assert(hashTable->Size > 0);
	assert(hashTable->Entries != NULL);

	eskilib_hashtable_free(hashTable);
}

void eskilib_hashtable_allocate_test()
{
	const size_t size = 16;

	eskilib_HashTable* hashTable = NULL;

	hashTable = eskilib_hashtable_allocate(size, sizeof(size_t*));

	assert(hashTable != NULL);
	assert(hashTable->Size == size);
	assert(hashTable->Entries != NULL);

	eskilib_hashtable_free(hashTable);
}

void eskilib_hashtable_release_tests()
{
}

void eskilib_hashtable_tests()
{
	#ifdef NDEBUG
		eskilib_hashtable_release_tests();	
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_hashtable_allocate_default_size_test", eskilib_hashtable_allocate_default_size_test);
	
	eskilib_test_run("eskilib_hashtable_allocate_test", eskilib_hashtable_allocate_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
