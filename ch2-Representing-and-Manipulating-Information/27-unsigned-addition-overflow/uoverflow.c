#include "uoverflow.h"

/* Return 0 if x + y overflows, and 1 otherwise */
int uadd_ok(unsigned x, unsigned y) {
    return (x + y) >= x;
}
