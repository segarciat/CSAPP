#include "div16.h"

int div16(int x) {
    // bias to ensure rounding up towards 0; note 16=2^4.
    static unsigned POW = 4;
    int bias = (0x10000000 & x) && 1; // bias by 0 (meaning not at all) if number is positive.
    return  (x + (bias << POW) - bias) >> POW;
}
