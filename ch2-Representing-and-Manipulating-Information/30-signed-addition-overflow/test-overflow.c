#include <glib.h>
#include <limits.h> // UINT_MAX
#include "toverflow.h"


void test_no_overflow() {
    g_assert_true(tadd_ok(0, 0));
    g_assert_true(tadd_ok(-52, -58));
    g_assert_true(tadd_ok(-52, 58));
    g_assert_true(tadd_ok(100, -27));
    g_assert_true(tadd_ok(100, 58));
    g_assert_true(tadd_ok(INT_MAX, 0));
    g_assert_true(tadd_ok(0, INT_MAX));
    g_assert_true(tadd_ok(INT_MIN, 0));
    g_assert_true(tadd_ok(0, INT_MIN));
}

void test_overflows() {
    g_assert_false(tadd_ok(INT_MAX, 1));
    g_assert_false(tadd_ok(1, INT_MAX));
    
    g_assert_false(tadd_ok(-1, INT_MIN));
    g_assert_false(tadd_ok(INT_MIN, -1));
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/nooverflow", test_no_overflow);
    g_test_add_func("/alltests/overflows", test_overflows);
    return g_test_run();
}
