#include <glib.h>
#include "div16.h"


void test_div16() {
    g_assert_cmpint(div16(0), ==, 0);
    g_assert_cmpint(div16(16), ==, 1);
    g_assert_cmpint(div16(47), ==, 2);
    g_assert_cmpint(div16(-16), ==, -1);
    g_assert_cmpint(div16(-47), ==, -2);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/div16", test_div16);
    return g_test_run();
}
