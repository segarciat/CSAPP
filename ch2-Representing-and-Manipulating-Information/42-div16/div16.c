#include "div16.h"

#define N 4

/* Returns x divided by 2^4 */
int div16(int x) {
	/* bias if x is negative (to round up to 0) or not otherwise round down to 0 */
    int bias = (0x10000000 & x) && 1;
    return  (x + (bias << N) - bias) >> N;
}
