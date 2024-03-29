#include <glib.h>
#include "leftmost_one.h"

void test_leftmost_one() {
	g_assert_cmphex(leftmost_one(0xFF00), ==, 0x8000);
	g_assert_cmphex(leftmost_one(0x6600), ==, 0x4000);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/leftmost_one", test_leftmost_one);
	return g_test_run();
}
