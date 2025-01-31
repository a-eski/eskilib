#include <stdlib.h>
#include <string.h>

#include "../eski_string.h"
#include "../eski_test.h"

#define eski_BUFFER_SIZE 64

void eski_string_copy_true_test(void)
{
	char* copyOne = "hello";
	char* copyOneBuffer = malloc(sizeof(char) * eski_BUFFER_SIZE);
	copyOne = eski_string_copy(copyOneBuffer, copyOne, eski_BUFFER_SIZE);
	eski_assert(strcmp(copyOne,copyOneBuffer) == 0);
	free(copyOneBuffer);
}

void eski_string_copy_false_test(void)
{
	char* copyTwo = "hello there";
	char* copyTwoBuffer = malloc(sizeof(char) * eski_BUFFER_SIZE);
	copyTwo = eski_string_copy(copyTwoBuffer, copyTwo, eski_BUFFER_SIZE);
	eski_assert(strcmp(copyTwo,copyTwoBuffer) == 0);
	free(copyTwoBuffer);
}

void eski_string_copy_over_buffer_limit_test(void)
{
	char* copyTwo = "hello there";
	char* copyTwoBuffer = malloc(sizeof(char) * eski_BUFFER_SIZE);
	copyTwo = eski_string_copy(copyTwoBuffer, copyTwo, 2);
	eski_assert(strcmp(copyTwo,copyTwoBuffer) == 0);
	free(copyTwoBuffer);
}

void eski_string_compare_true_test(void)
{
	int resultOne = eski_string_compare("Hello", "Hello", eski_BUFFER_SIZE);
	eski_assert(resultOne == 0);
}

void eski_string_compare_false_test(void)
{
	int resultTwo = eski_string_compare("Hello", "Hello there", eski_BUFFER_SIZE);
	eski_assert(resultTwo != 0);
}

void eski_string_compare_over_buffer_limit_test(void)
{
	int resultThree = eski_string_compare("Hello", "Hello there", 3);
	eski_assert(resultThree == -1);
}

void eski_string_contains_unsafe_true_test(void) {
	bool result = eski_string_contains_unsafe("ls -l", "ls");

	eski_assert(result == true);
}

void eski_string_contains_unsafe_false_test(void) {
	bool result = eski_string_contains_unsafe("ls -l", "nvim");

	eski_assert(result == false);
}

void eski_string_contains_true_test(void) {
	struct eski_String string = { .value = "ls -l", .length = 6 };
	struct eski_String substring = { .value = "ls", .length = 3 };

	bool result = eski_string_contains(string, substring);

	eski_assert(result == true);
}

void eski_string_contains_false_test(void) {
	struct eski_String string = { .value = "ls -l", .length = 6 };
	struct eski_String substring = { .value = "nvim", .length = 5 };

	bool result = eski_string_contains(string, substring);

	eski_assert(result == false);
}

void eski_string_contains_end_of_string_test(void) {
	struct eski_String string = { .value = "C:\\Users\\Alex\\source\\repos\\PersonalRepos\\shells\\ncsh", .length = 53};
	struct eski_String substring = { .value = "ncsh", .length = 5 };

	bool result_unsafe = eski_string_contains_unsafe(string.value, substring.value);

	eski_assert(result_unsafe == true);

	bool result = eski_string_contains(string, substring);

	eski_assert(result == true);

}

void eski_string_release_tests(void)
{
}

void eski_string_tests(void)
{
	eski_test_start();

	#ifdef NDEBUG
		eski_string_release_tests();
	#endif /* ifdef NDEBUG */

	eski_test_run("eski_string_copy_true_test", eski_string_copy_true_test);
	eski_test_run("eski_string_copy_false_test", eski_string_copy_true_test);
	eski_test_run("eski_string_compare_true_test", eski_string_compare_true_test);
	eski_test_run("eski_string_compare_false_test", eski_string_compare_false_test);
	eski_test_run("eski_string_contains_unsafe_false_test", eski_string_contains_unsafe_false_test);
	eski_test_run("eski_string_contains_unsafe_true_test", eski_string_contains_unsafe_true_test);
	eski_test_run("eski_string_contains_false_test", eski_string_contains_false_test);
	eski_test_run("eski_string_contains_true_test", eski_string_contains_true_test);
	eski_test_run("eski_string_contains_end_of_string_test", eski_string_contains_end_of_string_test);

	eski_test_finish();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_string_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
