#include <stdbool.h>
#include <stddef.h>
#include "eskilib_hashtable.h"
#include "eskilib_test.h"
#include "primitives/eskilib_string.h"

void eskilib_hashtable_malloc_default_size_test(void) {
	struct eskilib_HashTable hashtable = {0};

	enum eskilib_HashTable_Result result = eskilib_hashtable_malloc(0, &hashtable);
	eskilib_assert(result == HT_SUCCESS);

	eskilib_assert(hashtable.size > 0);
	eskilib_assert(hashtable.position == 0);
	eskilib_assert(hashtable.entries != NULL);

	eskilib_hashtable_free(&hashtable);
}

void eskilib_hashtable_malloc_test(void) {
	const size_t size = 16;

	struct eskilib_HashTable hashtable = {0};

	enum eskilib_HashTable_Result result = eskilib_hashtable_malloc(size, &hashtable);
	eskilib_assert(result == HT_SUCCESS);

	eskilib_assert(hashtable.size == size);
	eskilib_assert(hashtable.position == 0);
	eskilib_assert(hashtable.entries != NULL);

	eskilib_hashtable_free(&hashtable);
}

void eskilib_hashtable_add_one_test() {
	struct eskilib_HashTable hashtable = {0};

	enum eskilib_HashTable_Result result = eskilib_hashtable_malloc(0, &hashtable);
	eskilib_assert(result == HT_SUCCESS);

	const char* key = eskilib_hashtable_add("test", "success", &hashtable);

	eskilib_assert(key != NULL);
	eskilib_assert(eskilib_string_equals((char*)key, "test", 5));
	eskilib_assert(hashtable.position == 1);
	eskilib_assert(eskilib_string_equals((char*)hashtable.entries[hashtable.position].key, "test", 5));
	eskilib_assert(eskilib_string_equals((char*)hashtable.entries[hashtable.position].value, "success", 8));

	eskilib_hashtable_free(&hashtable);
}

void eskilib_hashtable_release_tests(void)
{
}

void eskilib_hashtable_tests(void)
{
	#ifdef NDEBUG
		eskilib_hashtable_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_hashtable_malloc_default_size_test", eskilib_hashtable_malloc_default_size_test);
	eskilib_test_run("eskilib_hashtable_malloc_test", eskilib_hashtable_malloc_test);
	eskilib_test_run("eskilib_hashtable_add_one_test", eskilib_hashtable_add_one_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
