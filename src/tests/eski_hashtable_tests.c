#include <stdbool.h>
#include <stddef.h>
#include "../eski_hashtable.h"
#include "../eski_test.h"

void eski_hashtable_malloc_default_size_test(void) {

	struct eski_HashTable ht;
	bool result = eski_hashtable_malloc(&ht);
	eski_assert(result);

	eski_assert(ht.capacity > 0);
	eski_assert(ht.length == 0);
	eski_assert(ht.entries != NULL);

	eski_hashtable_free(&ht);
}

void eski_hashtable_add_one_test(void) {

	struct eski_HashTable ht;
	bool result = eski_hashtable_malloc(&ht);
	eski_assert(result);

	const char* key_value = "hello";
	struct eski_String string = { .value = "world", .length = 6 };
	const char* key = eski_hashtable_set(key_value, string, &ht);

	eski_assert(key != NULL);
	eski_assert(eski_string_equals((char*)key, (char*)key_value, 6));
	eski_assert(ht.capacity > 0);
	eski_assert(ht.length == 1);

	struct eski_String result_string = eski_hashtable_get(key_value, &ht);
	eski_assert(result_string.value != NULL);
	eski_assert(result_string.length == string.length);
	eski_assert(eski_string_equals(string.value, result_string.value, string.length));

	eski_hashtable_free(&ht);
}

void eski_hashtable_add_multiple_test(void) {
	struct eski_HashTable ht;
	bool result = eski_hashtable_malloc(&ht);
	eski_assert(result);

	const char* key_value_one = "hello";
	struct eski_String string_one = { .value = "world", .length = 6 };
	const char* key_value_two = "test";
	struct eski_String string_two = { .value = "success", .length = 8 };

	const char* key_one = eski_hashtable_set(key_value_one, string_one, &ht);
	const char* key_two = eski_hashtable_set(key_value_two, string_two, &ht);

	eski_assert(ht.capacity > 0);
	eski_assert(ht.length == 2);

	eski_assert(key_one != NULL);
	eski_assert(eski_string_equals((char*)key_one, (char*)key_value_one, 6));

	eski_assert(key_two != NULL);
	eski_assert(eski_string_equals((char*)key_two, (char*)key_value_two, 5));


	struct eski_String result_one = eski_hashtable_get(key_value_one, &ht);
	eski_assert(result_one.value != NULL);
	eski_assert(result_one.length == string_one.length);
	eski_assert(eski_string_equals(result_one.value, string_one.value, result_one.length));

	struct eski_String result_two = eski_hashtable_get(key_value_two, &ht);
	eski_assert(result_two.value != NULL);
	eski_assert(result_two.length = string_two.length)
	eski_assert(eski_string_equals(result_two.value, string_two.value, result_two.length));

	eski_hashtable_free(&ht);
}

void eski_hashtable_add_duplicate_test(void) {

	struct eski_HashTable ht;
	bool result = eski_hashtable_malloc(&ht);
	eski_assert(result);

	const char* key_value = "hello";
	struct eski_String string = { .value = "world", .length = 6 };
	const char* key = eski_hashtable_set(key_value, string, &ht);
	eski_hashtable_set(key_value, string, &ht);

	eski_assert(eski_string_equals((char*)key, (char*)key_value, 6));
	eski_assert(ht.length == 1);

	eski_hashtable_free(&ht);
}

void eski_hashtable_release_tests(void) {

}

void eski_hashtable_tests(void) {
	eski_test_start();

	#ifdef NDEBUG
		eski_hashtable_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_hashtable_malloc_default_size_test", eski_hashtable_malloc_default_size_test);
	eski_test_run("eski_hashtable_add_one_test", eski_hashtable_add_one_test);
	eski_test_run("eski_hashtable_add_multiple_test", eski_hashtable_add_multiple_test);
	eski_test_run("eski_hashtable_add_duplicate_test", eski_hashtable_add_duplicate_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void) {
	eski_hashtable_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
