#include <glib.h>
#include <limits.h>
#include "right_shifts.h"

void test_logical_right_shifts() {
	g_assert_cmphex(srl(0x0, 8), ==, 0x0);
	g_assert_cmphex(srl(0x1234, 8), ==, 0x12);
	unsigned expected = (unsigned) -1 >> 8;
	g_assert_cmphex(srl(-1, 8), ==, expected);
}

void test_arithmetic_right_shifts() {
	g_assert_cmphex(sra(0, 8), ==, 0);
	g_assert_cmphex(sra(-1, 8), ==, -1);
	g_assert_cmphex(sra(0x1234, 8), ==, 0x12);
	g_assert_cmphex(sra(INT_MIN, 8), ==, INT_MIN >> 8);
	g_assert_cmphex(sra(INT_MAX, 8), ==, INT_MAX >> 8);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/logical_right_shifts", test_logical_right_shifts);
    g_test_add_func("/alltests/arithmetic_right_shifts", test_arithmetic_right_shifts);
	return g_test_run();
}
