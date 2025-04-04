#include "elist_value_tests.h"
#include "elist_struct_tests.h"
#include "elist_pointer_tests.h"

void elist_tests(void)
{
	elist_value_tests();
	elist_struct_tests();
	elist_pointer_tests();
}

#ifndef etest_ALL
int main(void)
{
	elist_tests();

	return 0;
}
#endif /* ifndef etest_ALL */
