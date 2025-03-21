#include <stdlib.h>
#include <string.h>

#include "../eskilib_string.h"
#include "../eskilib_test.h"

#define eskilib_BUFFER_SIZE 64

void eskilib_string_compare_true_test(void)
{
	char* val = "hello";
	const size_t len = sizeof("hello") - 1;
	bool result = eskilib_string_compare(val, len, val, len);
	eskilib_assert(result);
}

void eskilib_string_compare_false_test(void)
{
	char* val = "hello";
	const size_t len = sizeof("hello");
	char* val_two = "hello there";
	const size_t len_two = sizeof("hello there");

	bool result = eskilib_string_compare(val, len, val_two, len_two);

	eskilib_assert(!result);
}

void eskilib_string_contains_true_test(void) {
	struct eskilib_String string = { .value = "ls -l", .length = 6 };
	struct eskilib_String substring = { .value = "ls", .length = 3 };

	bool result = eskilib_string_contains(string.value, string.length, substring.value, substring.length);

	eskilib_assert(result);
}

void eskilib_string_contains_false_test(void) {
	struct eskilib_String string = { .value = "ls -l", .length = 6 };
	struct eskilib_String substring = { .value = "nvim", .length = 5 };

	bool result = eskilib_string_contains(string.value, string.length, substring.value, substring.length);

	eskilib_assert(!result);
}

void eskilib_string_contains_middle_of_string_test(void) {
	struct eskilib_String string = { .value = "C:\\Users\\Alex\\source\\repos\\PersonalRepos\\shells\\ncsh", .length = 53};
	struct eskilib_String substring = { .value = "source", .length = 7 };

	bool result = eskilib_string_contains(string.value, string.length, substring.value, substring.length);

	eskilib_assert(result);
}

void eskilib_string_contains_end_of_string_test(void) {
	struct eskilib_String string = { .value = "C:\\Users\\Alex\\source\\repos\\PersonalRepos\\shells\\ncsh", .length = 53};
	struct eskilib_String substring = { .value = "ncsh", .length = 5 };

	bool result = eskilib_string_contains(string.value, string.length, substring.value, substring.length);

	eskilib_assert(result);
}

void eskilib_string_release_tests(void)
{
}

void eskilib_string_tests(void)
{
	eskilib_test_start();

	#ifdef NDEBUG
		eskilib_string_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run(eskilib_string_compare_true_test);
	eskilib_test_run(eskilib_string_compare_false_test);
	eskilib_test_run(eskilib_string_contains_false_test);
	eskilib_test_run(eskilib_string_contains_true_test);
	eskilib_test_run(eskilib_string_contains_middle_of_string_test);
	eskilib_test_run(eskilib_string_contains_end_of_string_test);

	eskilib_test_finish();
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_string_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
