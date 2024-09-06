#include <stdio.h>
#include <stdlib.h>

void eskilib_output_allocation_error_and_exit(char* errorMessage)
{
	fprintf(stderr, "%s", errorMessage);
	exit(EXIT_FAILURE);
}

void eskilib_output_allocation_error_and_execute(char* errorMessage, void (*function)())
{
	fprintf(stderr, "%s", errorMessage);
	function();
}
