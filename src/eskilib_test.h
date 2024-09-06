#ifndef eskilib_test_h
#define eskilib_test_h

#include <stdio.h>

#define eskilib_assert(condition) if (!(condition)) printf("%s condition failed on line %d", __func__, __LINE__);

void eskilib_test_run(const char* function_name, void (*function)(void));

#endif /* !eskilib_test_h */

