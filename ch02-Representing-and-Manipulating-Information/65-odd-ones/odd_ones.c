int odd_ones(unsigned x) {
	// xor all bits of x (32 bits means 31 (bit-level) xor operations).
	int xr16 = x ^ ( x >> 16);
	int xr8 = xr16 ^ (xr16 >> 8);
	int xr4 = xr8 ^ (xr8 >> 4);
	int xr2 = xr4 ^ (xr4 >> 2);
	int xr1 = xr2 ^ (xr2 >> 1);

	// Result of 31 xor operations is in least significant bit.
	return (xr1 & 1) || 0;
}
