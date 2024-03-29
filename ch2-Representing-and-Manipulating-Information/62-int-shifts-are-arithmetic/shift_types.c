#include <stdio.h>

/* Returns 1 if right shifts are arithmetic on this machine, 0 otherwise */
int shift_types_are_arithmetic()
{
	return -1 == (-1 >> 1);
}

int main(int arc, char *argv[])
{
	printf("Right shifts on int are %s\n", shift_types_are_arithmetic() ? "arithmetic" : "logical");
}
