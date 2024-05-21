#include <stdio.h>
#include <glib.h>

int64_t swizzle(int64_t x, int64_t y) {
	return (x & 0xFF) | (y & ~0xFF);
}

void test_swizzle() {
	g_assert_cmphex(swizzle(0x89ABCDEF, 0x76543210), ==, 0x0765432EF);
}

int main(int argc, char **argv) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/alltests/swizzle", test_swizzle);
	return g_test_run();
}
