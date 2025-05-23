/* Copyright eskilib (C) by Alex Eski 2024 */

#ifndef ESKILIB_ETEST_H_
#define ESKILIB_ETEST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#define eassert(condition)                                                                                      \
    if (!(condition)) {                                                                                                \
        printf("%s condition (%s) failed on line %d\n", __func__, #condition, __LINE__);                               \
        etest_failed_internal();                                                                                \
        return;                                                                                                        \
    }

#define etest_run(function) etest_run_internal(#function, function);

extern void etest_run_internal(const char* function_name, void (*function)(void));

// private API: do not need to use this manually, used with eskilib_assert to mark test failed when assertion does not
// pass.
extern void etest_failed_internal(void);

// private API: is called at the start of a series of tests.
extern void etest_start_internal(char*);

// Call at the start of a series of tests
#define etest_start() etest_start_internal(__FILE__);

// private API: is called at the end of a series of tests for a summary.
extern void etest_finish_internal(char* file);

// Call at the end of a series of tests
#define etest_finish() etest_finish_internal(__FILE__);

#ifdef __cplusplus
}
#endif

#endif /* !ESKILIB_ETEST_H_ */
