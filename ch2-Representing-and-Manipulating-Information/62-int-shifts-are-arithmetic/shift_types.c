#include <stdio.h>
int shift_types_are_arithmetic()
{
	int width = 8 * sizeof(int);
	int msbit = -1 >> width;
	return msbit || 0;
}

int main(int arc, char *argv[])
{
	printf("%d\n", shift_types_are_arithmetic());
}
