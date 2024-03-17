#include "replace_byte.h"

unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	// if (i < 0 || i >= sizeof(x))
	//	return -1;
	int shiftAmount = 8 * i;
	return (x & ~(0xFF << shiftAmount)) | (b << shiftAmount);
	// return b << shiftAmount;
	// return (x & ~(0xFF << shiftAmount));
}
