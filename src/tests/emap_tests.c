/* Copyright (C) eskilib by Alex Eski 2025 */

#include <stdbool.h>
#include <stddef.h>
#include "../emap.h"
#include "../estr.h"
#include "../etest.h"

void emap_malloc_default_size_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eassert(result);

	eassert(hmap.capacity > 0);
	eassert(hmap.size == 0);
	eassert(hmap.entries != NULL);

	emap_free(&hmap);
}

void emap_add_one_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eassert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = emap_set(key_val, string, &hmap);

	eassert(key != NULL);
	eassert(!memcmp((char*)key, (char*)key_val, 6));
	eassert(hmap.capacity > 0);
	eassert(hmap.size == 1);

	struct estr result_string = emap_get(key_val, &hmap);
	eassert(result_string.val != NULL);
	eassert(result_string.len == string.len);
	eassert(!memcmp(string.val, result_string.val, string.len));

	emap_free(&hmap);
}

void emap_add_multiple_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eassert(result);

	const char* key_val_one = "hello";
	struct estr string_one = { .val = "world", .len = 6 };
	const char* key_val_two = "test";
	struct estr string_two = { .val = "success", .len = 8 };

	const char* key_one = emap_set(key_val_one, string_one, &hmap);
	const char* key_two = emap_set(key_val_two, string_two, &hmap);

	eassert(hmap.capacity > 0);
	eassert(hmap.size == 2);

	eassert(key_one != NULL);
	eassert(!memcmp((char*)key_one, (char*)key_val_one, 6));

	eassert(key_two != NULL);
	eassert(!memcmp((char*)key_two, (char*)key_val_two, 5));


	struct estr result_one = emap_get(key_val_one, &hmap);
	eassert(result_one.val != NULL);
	eassert(result_one.len == string_one.len);
	eassert(!memcmp(result_one.val, string_one.val, result_one.len));

	struct estr result_two = emap_get(key_val_two, &hmap);
	eassert(result_two.val != NULL);
	eassert(result_two.len = string_two.len)
	eassert(!memcmp(result_two.val, string_two.val, result_two.len));

	emap_free(&hmap);
}

void emap_add_duplicate_test(void)
{
	emap hmap;
	bool result = emap_malloc(&hmap);
	eassert(result);

	const char* key_val = "hello";
	struct estr string = { .val = "world", .len = 6 };
	const char* key = emap_set(key_val, string, &hmap);
	emap_set(key_val, string, &hmap);

	eassert(!memcmp((char*)key, (char*)key_val, 6));
	eassert(hmap.size == 1);

	emap_free(&hmap);
}

void emap_tests(void) {
	etest_start();

	etest_run(emap_malloc_default_size_test);
	etest_run(emap_add_one_test);
	etest_run(emap_add_multiple_test);
	etest_run(emap_add_duplicate_test);

	etest_finish();
}

#ifndef etest_ALL
int main(void) {
	emap_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
