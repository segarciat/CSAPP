#include "mysystem.h"
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
	if (argc != 2) {
		fprintf(stderr, "%s: Provide a single command (if it has arguments, quote it)\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	int status = mysystem(argv[1]);
	printf("\nStatus of child was: %d\n", status);
	exit(EXIT_SUCCESS);
}
