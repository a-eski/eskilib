#include <stdbool.h>
#include <stddef.h>
#include "eskilib_hashtable.h"
#include "eskilib_test.h"

void eskilib_hashtable_malloc_default_size_test()
{
	eskilib_HashTable* hashTable = NULL;

	hashTable = eskilib_hashtable_malloc(0, sizeof(size_t*));

	eskilib_assert(hashTable != NULL);
	eskilib_assert(hashTable->size > 0);
	eskilib_assert(hashTable->entries != NULL);

	eskilib_hashtable_free(hashTable);
}

void eskilib_hashtable_malloc_test()
{
	const size_t size = 16;

	eskilib_HashTable* hashTable = NULL;

	hashTable = eskilib_hashtable_malloc(size, sizeof(size_t*));

	eskilib_assert(hashTable != NULL);
	eskilib_assert(hashTable->size == size);
	eskilib_assert(hashTable->entries != NULL);

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

	eskilib_test_run("eskilib_hashtable_malloc_default_size_test", eskilib_hashtable_malloc_default_size_test);
	
	eskilib_test_run("eskilib_hashtable_malloc_test", eskilib_hashtable_malloc_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
