#include <stdio.h>
#include <time.h>

void eskilib_time_function(char* function_name, void (*function)())
{
	clock_t startTime;
	clock_t endTime;
	clock_t timeElapsed;

	printf("%s is starting under timer", function_name);

	startTime = clock() / CLOCKS_PER_SEC;

	function();

	endTime = clock() / CLOCKS_PER_SEC;

	timeElapsed = startTime - endTime;

	printf("%s ran for %ld clock cycles per second.", function_name, timeElapsed);
}
