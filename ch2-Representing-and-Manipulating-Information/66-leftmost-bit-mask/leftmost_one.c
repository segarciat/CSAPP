/*
 * Generate mask indicating leftmost 1 in x. Assume w=32 (width of int)
 * For example, 0xFF00 -> 0x8000, and 0x6600 -> 0x4000
 * If x = 0, then return 0.
 */
int leftmost_one(unsigned x)
{
	unsigned x1 = x | (x >> 16);
	unsigned x2 = x1 | (x1 >> 8);
	unsigned x3 = x2 | (x2 >> 4);
	unsigned x4 = x3 | (x3 >> 2);
	unsigned transformedx = x4 | (x4 >> 1);

	return (transformedx - (transformedx >> 1));
}
