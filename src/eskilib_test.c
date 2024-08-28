#include <stdio.h>

void eskilib_test_run(char* function_name, void (*function)())
{
	printf("\x1B[37m%s started.\n", function_name);

	function();

	printf("\x1B[32m%s passed.\n", function_name);
}
