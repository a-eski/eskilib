/* Copyright (C) eskilib by Alex Eski 2025 */

#include <stdbool.h>
#include <stddef.h>
#include "../emap.h"
#include "../estr.h"
#include "../eskilib_test.h"

void emap_malloc_default_size_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eskilib_assert(result);

	eskilib_assert(hmap.capacity > 0);
	eskilib_assert(hmap.size == 0);
	eskilib_assert(hmap.entries != NULL);

	emap_free(&hmap);
}

void emap_add_one_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eskilib_assert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = emap_set(key_val, string, &hmap);

	eskilib_assert(key != NULL);
	eskilib_assert(!memcmp((char*)key, (char*)key_val, 6));
	eskilib_assert(hmap.capacity > 0);
	eskilib_assert(hmap.size == 1);

	struct estr result_string = emap_get(key_val, &hmap);
	eskilib_assert(result_string.val != NULL);
	eskilib_assert(result_string.len == string.len);
	eskilib_assert(!memcmp(string.val, result_string.val, string.len));

	emap_free(&hmap);
}

void emap_add_multiple_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eskilib_assert(result);

	const char* key_val_one = "hello";
	struct estr string_one = { .val = "world", .len = 6 };
	const char* key_val_two = "test";
	struct estr string_two = { .val = "success", .len = 8 };

	const char* key_one = emap_set(key_val_one, string_one, &hmap);
	const char* key_two = emap_set(key_val_two, string_two, &hmap);

	eskilib_assert(hmap.capacity > 0);
	eskilib_assert(hmap.size == 2);

	eskilib_assert(key_one != NULL);
	eskilib_assert(!memcmp((char*)key_one, (char*)key_val_one, 6));

	eskilib_assert(key_two != NULL);
	eskilib_assert(!memcmp((char*)key_two, (char*)key_val_two, 5));


	struct estr result_one = emap_get(key_val_one, &hmap);
	eskilib_assert(result_one.val != NULL);
	eskilib_assert(result_one.len == string_one.len);
	eskilib_assert(!memcmp(result_one.val, string_one.val, result_one.len));

	struct estr result_two = emap_get(key_val_two, &hmap);
	eskilib_assert(result_two.val != NULL);
	eskilib_assert(result_two.len = string_two.len)
	eskilib_assert(!memcmp(result_two.val, string_two.val, result_two.len));

	emap_free(&hmap);
}

void emap_add_duplicate_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eskilib_assert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = emap_set(key_val, string, &hmap);
	emap_set(key_val, string, &hmap);

	eskilib_assert(!memcmp((char*)key, (char*)key_val, 6));
	eskilib_assert(hmap.size == 1);

	emap_free(&hmap);
}

void emap_tests(void) {
	eskilib_test_start();

	eskilib_test_run(emap_malloc_default_size_test);
	eskilib_test_run(emap_add_one_test);
	eskilib_test_run(emap_add_multiple_test);
	eskilib_test_run(emap_add_duplicate_test);

	eskilib_test_finish();
}

#ifndef ESKILIB_TEST_ALL
int main(void) {
	emap_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
