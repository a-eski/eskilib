#include <stdlib.h>
#include <string.h>

#include "../eskilib_string.h"
#include "../../eskilib_test.h"

#define ESKILIB_BUFFER_SIZE 64

void eskilib_string_copy_true_test(void)
{
	char* copyOne = "hello"; 
	char* copyOneBuffer = malloc(sizeof(char) * ESKILIB_BUFFER_SIZE);
	copyOne = eskilib_string_copy(copyOneBuffer, copyOne, ESKILIB_BUFFER_SIZE);
	eskilib_assert(strcmp(copyOne,copyOneBuffer) == 0);
	free(copyOneBuffer);
}

void eskilib_string_copy_false_test(void)
{
	char* copyTwo = "hello there";
	char* copyTwoBuffer = malloc(sizeof(char) * ESKILIB_BUFFER_SIZE);
	copyTwo = eskilib_string_copy(copyTwoBuffer, copyTwo, ESKILIB_BUFFER_SIZE);
	eskilib_assert(strcmp(copyTwo,copyTwoBuffer) == 0);
	free(copyTwoBuffer);
}

void eskilib_string_copy_over_buffer_limit_test(void)
{
	char* copyTwo = "hello there";
	char* copyTwoBuffer = malloc(sizeof(char) * ESKILIB_BUFFER_SIZE);
	copyTwo = eskilib_string_copy(copyTwoBuffer, copyTwo, 2);
	eskilib_assert(strcmp(copyTwo,copyTwoBuffer) == 0);
	free(copyTwoBuffer);
}

void eskilib_string_compare_true_test(void)
{
	int resultOne = eskilib_string_compare("Hello", "Hello", ESKILIB_BUFFER_SIZE);
	eskilib_assert(resultOne == 0);
}

void eskilib_string_compare_false_test(void)
{
	int resultTwo = eskilib_string_compare("Hello", "Hello there", ESKILIB_BUFFER_SIZE);
	eskilib_assert(resultTwo != 0);
}

void eskilib_string_compare_over_buffer_limit_test(void)
{
	int resultThree = eskilib_string_compare("Hello", "Hello there", 3);
	eskilib_assert(resultThree == -1);
}

void eskilib_string_release_tests(void)
{
}

void eskilib_string_tests(void)
{
	#ifdef NDEBUG
		eskilib_string_release_tests();
	#endif /* ifdef NDEBUG */

	eskilib_test_run("eskilib_string_copy_true_test", eskilib_string_copy_true_test);
	eskilib_test_run("eskilib_string_copy_false_test", eskilib_string_copy_true_test);
	eskilib_test_run("eskilib_string_compare_true_test", eskilib_string_compare_true_test);
	eskilib_test_run("eskilib_string_compare_false_test", eskilib_string_compare_false_test);
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_string_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
