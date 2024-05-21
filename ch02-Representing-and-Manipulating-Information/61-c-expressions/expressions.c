int any1bit(int x) {
	return x || 0;
}

int any0bit(int x) {
	return ~x || 0;
}

/* Returns 1 if any 1 bit in least significant byte exists, 0 otherwise */
int lsbyte1bit(int x) {
	return (x & 0xFF) || 0;
}

/* Returns 1 if any 0 bit in most significant byte exists, 0 otherwise */
int msbyte0bit(int x) {
	// if x msbyte is only 1s, arithmetic right shifts fills with 1s.
	// return (x >> (8*sizeof(int)-1)) != -1;
	int shiftval = (sizeof(int) - 1) << 3;
	return ((x >> shiftval) & 0xFF) != 0xFF // alternative when >> is logical
}
