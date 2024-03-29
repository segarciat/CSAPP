#include <stdint.h> // int64_t
#include "tmultof.h"

/* Returns 0 if x * y overflows, and 1 otherwise. */
int tmult_ok(int x, int y) {
	/* Extend to 64 bits before multiplying; product fits */
    int64_t p = (int64_t) x * y;
	/* Verify truncated bit pattern remains equivalent */
    return p == (int) p; 
}
