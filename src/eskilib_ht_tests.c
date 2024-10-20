#include <stdbool.h>
#include <stddef.h>
#include "eskilib_ht.h"
#include "eskilib_test.h"
#include "primitives/eskilib_string.h"

void eskilib_ht_malloc_default_size_test(void) {

	struct eskilib_ht ht;
	bool result = eskilib_ht_malloc(&ht);
	eskilib_assert(result);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 0);
	eskilib_assert(ht.entries != NULL);

	eskilib_ht_free(&ht);
}

void eskilib_ht_add_one_test(void) {

	struct eskilib_ht ht;
	bool result = eskilib_ht_malloc(&ht);
	eskilib_assert(result);

	const char* key = eskilib_ht_set("hello", "world", &ht);

	eskilib_assert(key != NULL);
	eskilib_assert(eskilib_string_equals((char*)key, "hello", 6));
	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 1);

	const char* value = eskilib_ht_get("hello", &ht);
	eskilib_assert(value != NULL);
	eskilib_assert(eskilib_string_equals((char*)value, "world", 6));

	eskilib_ht_free(&ht);
}

void eskilib_ht_add_multiple_test(void) {
	struct eskilib_ht ht;
	bool result = eskilib_ht_malloc(&ht);
	eskilib_assert(result);

	const char* key_one = eskilib_ht_set("hello", "world", &ht);
	const char* key_two = eskilib_ht_set("test", "success", &ht);

	eskilib_assert(ht.capacity > 0);
	eskilib_assert(ht.length == 2);

	eskilib_assert(key_one != NULL);
	eskilib_assert(eskilib_string_equals((char*)key_one, "hello", 6));

	eskilib_assert(key_two != NULL);
	eskilib_assert(eskilib_string_equals((char*)key_two, "test", 5));


	const char* value_one = eskilib_ht_get("hello", &ht);
	eskilib_assert(value_one != NULL);
	eskilib_assert(eskilib_string_equals((char*)value_one, "world", 6));

	const char* value_two = eskilib_ht_get("test", &ht);
	eskilib_assert(value_two != NULL);
	eskilib_assert(eskilib_string_equals((char*)value_two, "success", 8));

	eskilib_ht_free(&ht);
}

void eskilib_ht_release_tests(void) {

}

void eskilib_ht_tests(void) {
	#ifdef NDEBUG
		eskilib_ht_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_ht_malloc_default_size_test", eskilib_ht_malloc_default_size_test);
	eskilib_test_run("eskilib_ht_add_one_test", eskilib_ht_add_one_test);
	eskilib_test_run("eskilib_ht_add_multiple_test", eskilib_ht_add_multiple_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void) {
	eskilib_ht_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
