#include <stdio.h>

int is_little_endian() {
	int x = 1;
	char *xaddr = (char*) &x;
	return xaddr[0]; /* Least significant byte, with value 1, appears at the beginning */
}
