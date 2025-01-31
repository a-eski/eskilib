/* Copyright eski by Alex Eski 2024 */

#ifndef eski_test_h
#define eski_test_h

#include <stdio.h>
#include <stdbool.h>

#define eski_assert(condition) if (!(condition)) { printf("%s condition failed on line %d\n", __func__, __LINE__); eski_test_failed_internal(); return; }

extern void eski_test_run(const char* function_name, void (*function)(void));

// private API: do not need to use this manually, used with eski_assert to mark test failed when assertion does not pass.
extern void eski_test_failed_internal(void);

// private API: is called at the start of a series of tests.
extern void eski_test_start_internal(char*);

// Call at the start of a series of tests
#define eski_test_start() eski_test_start_internal(__FILE__);

// private API: is called at the end of a series of tests for a summary.
extern void eski_test_finish_internal(char* file);

// Call at the end of a series of tests
#define eski_test_finish() eski_test_finish_internal(__FILE__);

#endif /* !eski_test_h */
