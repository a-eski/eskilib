#include <stdio.h>
#include <stdlib.h>

void eski_output_allocation_error_and_exit(char* errorMessage)
{
	fprintf(stderr, "%s", errorMessage);
	exit(EXIT_FAILURE);
}

void eski_output_allocation_error_and_execute(char* errorMessage, void (*function)(void))
{
	fprintf(stderr, "%s", errorMessage);
	function();
}
