#include <stdbool.h>
#include <stddef.h>
#include "eskilib_hashtable.h"
#include "eskilib_test.h"

void eskilib_hashtable_malloc_default_size_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 0);
	eskilib_assert(ht.entries != NULL);

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_one_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_value = "hello";
	struct eskilib_String string = { .value = "world", .length = 6 };
	const char* key = eskilib_hashtable_set(key_value, string, &ht);

	eskilib_assert(key != NULL);
	eskilib_assert(eskilib_string_equals((char*)key, (char*)key_value, 6));
	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 1);

	struct eskilib_String result_string = eskilib_hashtable_get(key_value, &ht);
	eskilib_assert(result_string.value != NULL);
	eskilib_assert(result_string.length == string.length);
	eskilib_assert(eskilib_string_equals(string.value, result_string.value, string.length));

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_multiple_test(void) {
	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_value_one = "hello";
	struct eskilib_String string_one = { .value = "world", .length = 6 };
	const char* key_value_two = "test";
	struct eskilib_String string_two = { .value = "success", .length = 8 };

	const char* key_one = eskilib_hashtable_set(key_value_one, string_one, &ht);
	const char* key_two = eskilib_hashtable_set(key_value_two, string_two, &ht);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 2);

	eskilib_assert(key_one != NULL);
	eskilib_assert(eskilib_string_equals((char*)key_one, (char*)key_value_one, 6));

	eskilib_assert(key_two != NULL);
	eskilib_assert(eskilib_string_equals((char*)key_two, (char*)key_value_two, 5));


	struct eskilib_String result_one = eskilib_hashtable_get(key_value_one, &ht);
	eskilib_assert(result_one.value != NULL);
	eskilib_assert(result_one.length == string_one.length);
	eskilib_assert(eskilib_string_equals(result_one.value, string_one.value, result_one.length));

	struct eskilib_String result_two = eskilib_hashtable_get(key_value_two, &ht);
	eskilib_assert(result_two.value != NULL);
	eskilib_assert(result_two.length = string_two.length)
	eskilib_assert(eskilib_string_equals(result_two.value, string_two.value, result_two.length));

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_add_duplicate_test(void) {

	struct eskilib_HashTable ht;
	bool result = eskilib_hashtable_malloc(&ht);
	eskilib_assert(result);

	const char* key_value = "hello";
	struct eskilib_String string = { .value = "world", .length = 6 };
	const char* key = eskilib_hashtable_set(key_value, string, &ht);
	eskilib_hashtable_set(key_value, string, &ht);

	eskilib_assert(eskilib_string_equals((char*)key, (char*)key_value, 6));
	eskilib_assert(ht.length == 1);

	eskilib_hashtable_free(&ht);
}

void eskilib_hashtable_release_tests(void) {

}

void eskilib_hashtable_tests(void) {
	#ifdef NDEBUG
		eskilib_hashtable_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_hashtable_malloc_default_size_test", eskilib_hashtable_malloc_default_size_test);
	eskilib_test_run("eskilib_hashtable_add_one_test", eskilib_hashtable_add_one_test);
	eskilib_test_run("eskilib_hashtable_add_multiple_test", eskilib_hashtable_add_multiple_test);
	eskilib_test_run("eskilib_hashtable_add_duplicate_test", eskilib_hashtable_add_duplicate_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void) {
	eskilib_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
