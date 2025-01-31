#include "eski_list_value_tests.h"
#include "eski_list_struct_tests.h"

void eski_list_tests(void)
{
	eski_list_value_tests();
	eski_list_struct_tests();
}

#ifndef ESKI_TEST_ALL
int main(void)
{
	eski_list_tests();

	return 0;
}
#endif /* ifndef ESKI_TEST_ALL */
