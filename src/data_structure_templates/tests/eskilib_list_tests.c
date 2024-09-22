#include "eskilib_list_value_tests.h"
#include "eskilib_list_struct_tests.h"

void eskilib_list_tests(void)
{
	eskilib_list_value_tests();
	eskilib_list_struct_tests();
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
	eskilib_list_tests();

	return 0;
}
#endif /* ifndef ESKILIB_TEST_ALL */
