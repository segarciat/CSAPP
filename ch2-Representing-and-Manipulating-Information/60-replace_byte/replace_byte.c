#include "replace_byte.h"

#define BITS_IN_BYTE 8
/*
 * Replace byte at position i of x with b and returns it.
 *
 * 0 <= i <= sizeof(unsigned / 8) - 1,
 * (e.g., 0 < = i <= 7 if sizeof(unsigned) = 4 bytes)
 * Returns 0 on failure
 */
unsigned replace_byte(unsigned x, int i, unsigned char b)
{
	if (i < 0 || i >= sizeof(x))
		return 0;
	int shiftAmount = BITS_IN_BYTE * i;	
	unsigned clearByteMask = ~(0xFF << shiftAmount);
	return (x & clearByteMask) | (b << shiftAmount);
}
