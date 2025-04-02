#include <stdlib.h>
#include <string.h>

#include "../estr.h"
#include "../eskilib_test.h"

void estr_compare_no_length_test(void)
{
    char* val = "";
    constexpr size_t len = 0;
    bool result = estr_compare(val, len, val, len);
    eskilib_assert(!result);
}

void estr_compare_null_test(void)
{
    char* val = NULL;
    constexpr size_t len = 0;
    bool result = estr_compare(val, len, val, len);
    eskilib_assert(!result);
}

void estr_compare_empty_string_test(void)
{
    struct estr str = estr_Empty;
    bool result = estr_compare(str.value, str.length, str.value, str.length);
    eskilib_assert(!result);
}

void estr_compare_true_test(void)
{
    char* val = "hello";
    constexpr size_t len = sizeof("hello") - 1;
    bool result = estr_compare(val, len, val, len);
    eskilib_assert(result);
}

void estr_compare_false_test(void)
{
    const struct estr s1 = estr_New_Literal("hello hello");
    const struct estr s2 = estr_New_Literal("hello there");

    bool result = estr_compare(s1.value, s1.length, s2.value, s2.length);

    eskilib_assert(!result);
}

void estr_compare_mismatched_lengths_false_test(void)
{
    char* val = "hello";
    constexpr size_t len = sizeof("hello");
    char* val_two = "hello there";
    constexpr size_t len_two = sizeof("hello there");

    bool result = estr_compare(val, len, val_two, len_two);

    eskilib_assert(!result);
}

void estr_compare_partial_comparison_true_test(void)
{
    char* val = "hello";
    // only compare the first three characters, 'hel'
    constexpr size_t len = sizeof("hello") - 1 - 2;
    bool result = estr_compare(val, len, val, len);
    eskilib_assert(result);
}

void estr_compare_partial_comparison_false_test(void)
{
    const struct estr s1 = estr_New("hello hello", sizeof("hello hello") - 2);
    const struct estr s2 = estr_New("hello there", sizeof("hello there") - 2);

    bool result = estr_compare(s1.value, s1.length, s2.value, s2.length);

    eskilib_assert(!result);
}

void estr_compare_const_no_length_test(void)
{
    const char* val = "";
    constexpr size_t len = 0;
    bool result = estr_compare_const(val, len, val, len);
    eskilib_assert(!result);
}

void estr_compare_const_null_test(void)
{
    const char* val = NULL;
    constexpr size_t len = 0;
    bool result = estr_compare_const(val, len, val, len);
    eskilib_assert(!result);
}

void estr_compare_const_empty_string_test(void)
{
    const struct estr str = estr_Empty;
    bool result = estr_compare_const(str.value, str.length, str.value, str.length);
    eskilib_assert(!result);
}

void estr_compare_const_true_test(void)
{
    char* val = "hello";
    constexpr size_t len = sizeof("hello") - 1;
    bool result = estr_compare_const(val, len, val, len);
    eskilib_assert(result);
}

void estr_compare_const_false_test(void)
{
    char* val = "hello hello";
    constexpr size_t len = sizeof("hello hello");
    char* val_two = "hello there";
    constexpr size_t len_two = sizeof("hello there");

    bool result = estr_compare_const(val, len, val_two, len_two);

    eskilib_assert(!result);
}

void estr_compare_const_mismatched_lengths_false_test(void)
{
    char* val = "hello";
    constexpr size_t len = sizeof("hello");
    char* val_two = "hello there";
    constexpr size_t len_two = sizeof("hello there");

    bool result = estr_compare_const(val, len, val_two, len_two);

    eskilib_assert(!result);
}

void estr_compare_const_partial_comparison_true_test(void)
{
    char* val = "hello";
    // only compare the first three characters, 'hel'
    constexpr size_t len = sizeof("hello") - 1 - 2;
    bool result = estr_compare_const(val, len, val, len);
    eskilib_assert(result);
}

void estr_compare_const_partial_comparison_false_test(void)
{
    char* val = "hello hello";
    constexpr size_t len = sizeof("hello hello") - 1 - 2;
    char* val_two = "hello there";
    constexpr size_t len_two = sizeof("hello there") - 1 - 2;

    bool result = estr_compare_const(val, len, val_two, len_two);

    eskilib_assert(!result);
}

void estr_tests(void)
{
    eskilib_test_start();

    eskilib_test_run(estr_compare_no_length_test);
    eskilib_test_run(estr_compare_null_test);
    eskilib_test_run(estr_compare_empty_string_test);
    eskilib_test_run(estr_compare_true_test);
    eskilib_test_run(estr_compare_false_test);
    eskilib_test_run(estr_compare_mismatched_lengths_false_test);
    eskilib_test_run(estr_compare_partial_comparison_true_test);
    eskilib_test_run(estr_compare_partial_comparison_false_test);
    eskilib_test_run(estr_compare_const_no_length_test);
    eskilib_test_run(estr_compare_const_null_test);
    eskilib_test_run(estr_compare_const_empty_string_test);
    eskilib_test_run(estr_compare_const_true_test);
    eskilib_test_run(estr_compare_const_false_test);
    eskilib_test_run(estr_compare_const_mismatched_lengths_false_test);
    eskilib_test_run(estr_compare_const_partial_comparison_true_test);
    eskilib_test_run(estr_compare_const_partial_comparison_false_test);

    eskilib_test_finish();
}

#ifndef ESKILIB_TEST_ALL
int main(void)
{
    estr_tests();

    return EXIT_SUCCESS;
}
#endif /* ifndef ESKILIB_TEST_ALL */
