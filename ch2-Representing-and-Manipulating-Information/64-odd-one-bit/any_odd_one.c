/* Return 1 when any odd bit of x equals 1; 0 otherwise
 * Assume x is a 32-bit integer.
 */
int any_odd_one(unsigned x) {
	return (x & 0x55555555) || 0;
}
