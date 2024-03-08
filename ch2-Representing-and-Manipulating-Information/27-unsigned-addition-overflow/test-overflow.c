#include <glib.h>
#include <limits.h> // UINT_MAX
#include "overflow.h"


void test_no_overflow() {
    g_assert_true(uadd_ok(0, 0));
    g_assert_true(uadd_ok(42, 58));
    g_assert_true(uadd_ok(UINT_MAX, 0));
    g_assert_true(uadd_ok(0, UINT_MAX));
}

void test_overflows() {
    g_assert_false(uadd_ok(UINT_MAX, 1));
    g_assert_false(uadd_ok(1, UINT_MAX));
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/nooverflow", test_no_overflow);
    g_test_add_func("/alltests/overflows", test_overflows);
    return g_test_run();
}
