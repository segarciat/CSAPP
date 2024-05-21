#include "toverflow.h"

/* Returns 0 if x + y overflows, and 1 otherwise */
int tadd_ok(int x, int y) {
    int sum = x + y;
	/* Operands have different signs, or result and operand have same sign*/
	return ((x >= 0) != (y >= 0)) || ((sum >= 0) == (x >= 0));
}
