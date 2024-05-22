#include <stdio.h> /* fprintf(), printf(), stderr */
#include <stdlib.h> /* exit() EXIT_FAILURE */
#include <string.h> /* strcmp(), strerror() */
#include <errno.h> /* errno */
#include <unistd.h> /* STDOUT_FILENO, write(), fstat() */
#include <sys/types.h> /* off_t */
#include <fcntl.h> /* open(), O_RDONLY */
#include <sys/mman.h> /* mmap() */
#include <sys/stat.h> /* struct stat, fstat() */

#define FILE_ARG_IDX 1

void
unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	/* Validate command-line arguments */
	if (argc != 2 || strcmp("--help", argv[1]) == 0) {
		fprintf(stderr, "Usage: %s filename\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Open input file */
	int fd = open(argv[FILE_ARG_IDX], O_RDONLY);
	if (fd == -1)
		unix_error("Failed to open input file");

	/* Get file size */
	struct stat sb;
	if (fstat(fd, &sb) == -1)
		unix_error("Failed to get file size");
		
	/* Get memory map */
	off_t offset = 0; /* Start at beginning of the file */
	void *start = NULL; /* Let kernel decide */
	char *bufp = mmap(start, sb.st_size, PROT_READ, MAP_PRIVATE, fd, offset);
	if (bufp == MAP_FAILED)
		unix_error("Failed to create memory mapping for input sile");

	/* Write to stdout */
	if (write(STDOUT_FILENO, bufp, sb.st_size) == -1)
		unix_error("Failed to write contents to stdout");
	exit(EXIT_SUCCESS);
}
