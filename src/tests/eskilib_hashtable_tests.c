#include <stdbool.h>
#include <stddef.h>
#include "../eskilib_hashtable.h"
#include "../estr.h"
#include "../eskilib_test.h"

void eskilib_hashtable_malloc_default_size_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.size == 0);
	eskilib_assert(ht.entries != NULL);

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_one_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = eskilib_hashtable_set(key_val, string, &ht);

	eskilib_assert(key != NULL);
	eskilib_assert(!memcmp((char*)key, (char*)key_val, 6));
	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.size == 1);

	struct estr result_string = eskilib_hashtable_get(key_val, &ht);
	eskilib_assert(result_string.val != NULL);
	eskilib_assert(result_string.len == string.len);
	eskilib_assert(!memcmp(string.val, result_string.val, string.len));

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_multiple_test(void) {
	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_val_one = "hello";
	struct estr string_one = { .val = "world", .len = 6 };
	const char* key_val_two = "test";
	struct estr string_two = { .val = "success", .len = 8 };

	const char* key_one = eskilib_hashtable_set(key_val_one, string_one, &ht);
	const char* key_two = eskilib_hashtable_set(key_val_two, string_two, &ht);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.size == 2);

	eskilib_assert(key_one != NULL);
	eskilib_assert(!memcmp((char*)key_one, (char*)key_val_one, 6));

	eskilib_assert(key_two != NULL);
	eskilib_assert(!memcmp((char*)key_two, (char*)key_val_two, 5));


	struct estr result_one = eskilib_hashtable_get(key_val_one, &ht);
	eskilib_assert(result_one.val != NULL);
	eskilib_assert(result_one.len == string_one.len);
	eskilib_assert(!memcmp(result_one.val, string_one.val, result_one.len));

	struct estr result_two = eskilib_hashtable_get(key_val_two, &ht);
	eskilib_assert(result_two.val != NULL);
	eskilib_assert(result_two.len = string_two.len)
	eskilib_assert(!memcmp(result_two.val, string_two.val, result_two.len));

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_duplicate_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = eskilib_hashtable_set(key_val, string, &ht);
	eskilib_hashtable_set(key_val, string, &ht);

	eskilib_assert(!memcmp((char*)key, (char*)key_val, 6));
	eskilib_assert(ht.size == 1);

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_release_tests(void) {

}

void eskilib_hashtable_tests(void) {
	eskilib_test_start();

	#ifdef NDEBUG
		eskilib_hashtable_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run(eskilib_hashtable_malloc_default_size_test);
	eskilib_test_run(eskilib_hashtable_add_one_test);
	eskilib_test_run(eskilib_hashtable_add_multiple_test);
	eskilib_test_run(eskilib_hashtable_add_duplicate_test);

	eskilib_test_finish();
}

#ifndef ESKILIB_TEST_ALL
int main(void) {
	eskilib_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
