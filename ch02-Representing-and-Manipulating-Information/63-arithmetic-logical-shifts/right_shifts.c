#define INT_WIDTH (8 * sizeof(int))

/* 0 <= k < INT_WIDTH */

/* Shifts x right by k logically */
unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;

	int desiredBits = (INT_WIDTH - k);

	/* All but first last k bits are 1 */
	int bitmask = ~((-1) << desiredBits);

	return xsra & bitmask;
}

/* Shift x right by k arithmetically */
int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;

	/* xmsbit is 1 or 0 */
	int xmsbit = (x & (1 << (INT_WIDTH - 1))) || 0;

	/* -1 if x is positive, 0 otherwise */
	int copiedxmsbit = ~(xmsbit - 1);

	/* Most significant k bits equal x's msbit, rest are 0 */
	int bitmask = copiedxmsbit << (INT_WIDTH - k);

	return xsrl | bitmask;
}
