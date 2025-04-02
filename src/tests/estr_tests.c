#include <stdlib.h>

#include "../estr.h"
#include "../eskilib_test.h"

void estr_compare_no_len_test(void)
{
    estr str = estr_New("", 0);

    bool result = estr_compare(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_null_test(void)
{
    estr str = estr_New(NULL, 0);

    bool result = estr_compare(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_empty_string_test(void)
{
    estr str = estr_Empty;

    bool result = estr_compare(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_true_test(void)
{
    estr str = estr_New("hello", sizeof("hello") - 1);

    bool result = estr_compare(str.val, str.len, str.val, str.len);

    eskilib_assert(result);
}

void estr_compare_false_test(void)
{
    estr s1 = estr_New_Literal("hello hello");
    estr s2 = estr_New_Literal("hello there");

    bool result = estr_compare(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_compare_mismatched_lens_false_test(void)
{
    estr s1 = estr_New_Literal("hello");
    estr s2 = estr_New_Literal("hello there");

    bool result = estr_compare(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_compare_partial_comparison_true_test(void)
{
    // only compare the first three characters, 'hel'
    estr str = estr_New("hello", sizeof("hello") - 1 - 2);

    bool result = estr_compare(str.val, str.len, str.val, str.len);

    eskilib_assert(result);
}

void estr_compare_partial_comparison_false_test(void)
{
    estr s1 = estr_New("hello hello", sizeof("hello hello") - 2);
    estr s2 = estr_New("hello there", sizeof("hello there") - 2);

    bool result = estr_compare(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_compare_const_no_len_test(void)
{
    estr str = estr_New("", 0);

    bool result = estr_compare_const(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_const_null_test(void)
{
    estr str = estr_New(NULL, 0);

    bool result = estr_compare_const(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_const_empty_string_test(void)
{
    estr str = estr_Empty;

    bool result = estr_compare_const(str.val, str.len, str.val, str.len);

    eskilib_assert(!result);
}

void estr_compare_const_true_test(void)
{
    estr str = estr_New("hello", sizeof("hello") - 1);

    bool result = estr_compare_const(str.val, str.len, str.val, str.len);

    eskilib_assert(result);
}

void estr_compare_const_false_test(void)
{
    estr s1 = estr_New_Literal("hello hello");
    estr s2 = estr_New_Literal("hello there");

    bool result = estr_compare_const(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_compare_const_mismatched_lens_false_test(void)
{
    estr s1 = estr_New_Literal("hello");
    estr s2 = estr_New_Literal("hello there");

    bool result = estr_compare_const(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_compare_const_partial_comparison_true_test(void)
{
    // only compare the first three characters, 'hel'
    estr str = estr_New("hello", sizeof("hello") - 1 - 2);

    bool result = estr_compare_const(str.val, str.len, str.val, str.len);

    eskilib_assert(result);
}

void estr_compare_const_partial_comparison_false_test(void)
{
    estr s1 = estr_New("hello hello", sizeof("hello hello") - 2);
    estr s2 = estr_New("hello there", sizeof("hello there") - 2);

    bool result = estr_compare_const(s1.val, s1.len, s2.val, s2.len);

    eskilib_assert(!result);
}

void estr_tests(void)
{
    eskilib_test_start();

    eskilib_test_run(estr_compare_no_len_test);
    eskilib_test_run(estr_compare_null_test);
    eskilib_test_run(estr_compare_empty_string_test);
    eskilib_test_run(estr_compare_true_test);
    eskilib_test_run(estr_compare_false_test);
    eskilib_test_run(estr_compare_mismatched_lens_false_test);
    eskilib_test_run(estr_compare_partial_comparison_true_test);
    eskilib_test_run(estr_compare_partial_comparison_false_test);
    eskilib_test_run(estr_compare_const_no_len_test);
    eskilib_test_run(estr_compare_const_null_test);
    eskilib_test_run(estr_compare_const_empty_string_test);
    eskilib_test_run(estr_compare_const_true_test);
    eskilib_test_run(estr_compare_const_false_test);
    eskilib_test_run(estr_compare_const_mismatched_lens_false_test);
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
