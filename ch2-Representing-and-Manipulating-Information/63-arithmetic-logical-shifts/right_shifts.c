#define INT_WIDTH (8 * sizeof(int))

/* 0 <= k < INT_WIDTH */
unsigned srl(unsigned x, int k) {
	/* Perform shift arithmetically */
	unsigned xsra = (int) x >> k;

	int desiredBits = (INT_WIDTH - k);

	/* All but first last k bits are 1 */
	int bitmask = ~((-1) << desiredBits);
	return xsra & bitmask;
}

int sra(int x, int k) {
	/* Perform shift logically */
	int xsrl = (unsigned) x >> k;

	/* msb is 1 or 0 */
	int msb = (x & (1 << (INT_WIDTH - 1))) || 0;

	/* all 1s or all 0s */
	int allMsbs = ~(msb - 1);

	/* All but first last k bits are 1 */
	int bitmask = allMsbs << (INT_WIDTH - k);

	return xsrl | bitmask;
}
