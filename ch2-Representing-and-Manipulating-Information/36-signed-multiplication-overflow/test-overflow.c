#include <glib.h>
#include <limits.h> // UINT_MAX
#include "tmultof.h"


void test_no_overflow() {
    g_assert_true(tmult_ok(INT_MAX, 1));
    g_assert_true(tmult_ok(INT_MAX, -1));
    g_assert_true(tmult_ok(INT_MIN, 1));
}

void test_overflows() {
    g_assert_false(tmult_ok(INT_MAX, 2));
    g_assert_false(tmult_ok(INT_MAX, INT_MAX));
    g_assert_false(tmult_ok(INT_MIN, INT_MIN));
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/nooverflow", test_no_overflow);
    g_test_add_func("/alltests/overflows", test_overflows);
    return g_test_run();
}
