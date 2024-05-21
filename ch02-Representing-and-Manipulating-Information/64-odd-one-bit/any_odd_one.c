/* Return 1 when any odd bit of x equals 1; 0 otherwise.
 * Assume x is a 32-bit integer.
 */
int any_odd_one(unsigned x) {
	/* 0x5 is 0101; if wanted even bits, could use 0xA, which equals 0x1010 */
	return (x & 0x55555555) || 0;
}
