#include <stdio.h>
#include "endianness.h"

int main(int argc, char *argv[])
{
	printf("%d\n", is_little_endian());
}
