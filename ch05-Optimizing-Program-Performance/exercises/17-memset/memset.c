#include "memset.h"
#include <stdio.h>
/* Basic implementation of memset (page 572) */
void *basic_memset(void *s, int c, size_t n)
{
	size_t cnt = 0;
	unsigned char *schar = s;
	while (cnt < n) {
		*schar++ = (unsigned char) c;
		cnt++;
	}
	return s;
}

#define K sizeof(unsigned long)

/* 
 * Fill n bytes of memory area starting at s with least significant byte in c.
 */
void *memset_improved(void *s, int c, size_t n)
{
	unsigned char cLSB = c;
	size_t cnt = 0;
	unsigned char *schar = s;

	/* Write bytes until schar is aligned on K-byte boundary (assume K is power of 2) */
	size_t alignLimit = (size_t) ((K - 1) & (unsigned long) s);
	size_t limit = (n < alignLimit) ? n : alignLimit;
	while (cnt < limit) {
		*schar++ = cLSB;
		cnt++;
	}

	/* Replicate LSB of c across */
	unsigned long cLSBword = 0;
	for (size_t i = 0; i < K; i++)
		cLSBword = (cLSBword << 8) | cLSB;
	
	/* Do word-level writes */
	unsigned long *slong = (unsigned long *) schar;
	limit = (n - cnt) >= K ? n - (K - 1) : 0;
	for (; cnt < limit ; cnt += K)
		*slong++ = cLSBword;
	
	/* Finish remaining bytes */
	schar = (unsigned char *) slong;
	while (cnt < n) {
		*schar++ = cLSB;
		cnt++;
	}
	return s;
}
