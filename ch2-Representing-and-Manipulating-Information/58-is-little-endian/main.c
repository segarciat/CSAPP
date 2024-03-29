#include <stdio.h>
#include "endianness.h"

int main(int argc, char *argv[])
{
	printf("Compiled and run on %s endian\n", is_little_endian() ? "little" : "big");
}
