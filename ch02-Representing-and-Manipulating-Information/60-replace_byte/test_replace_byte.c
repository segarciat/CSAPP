#include <glib.h>
#include "replace_byte.h"

void test_replace_byte() {
	g_assert_cmphex(replace_byte(0x12345678, 2, 0xAB), ==, 0x12AB5678);
	g_assert_cmphex(replace_byte(0x12345678, 0, 0xAB), ==, 0x123456AB);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/replace_byte", test_replace_byte);
	return g_test_run();
}
