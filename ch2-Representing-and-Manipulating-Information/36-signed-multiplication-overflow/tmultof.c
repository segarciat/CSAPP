#include <stdint.h> // int64_t
#include "tmultof.h"

int tmult_ok(int x, int y) {
    int64_t p = (int64_t) x * y;
    return p == (int) p; 
}
