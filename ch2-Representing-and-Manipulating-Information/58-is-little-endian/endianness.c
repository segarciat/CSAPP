#include <stdio.h>

/* Returns 1 when compiled and run on little-endian machine, 0 otherwise */
int is_little_endian() {
	int x = 1;
	char *xaddr = (char*) &x;
	return xaddr[0]; /* Least significant byte, with value 1, appears at the beginning */
}
