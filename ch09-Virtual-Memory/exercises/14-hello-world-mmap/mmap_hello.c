#include <string.h> /* strcmp(), strerror() */
#include <errno.h> /* errno */
#include <stdio.h> /* fprintf(), stderr */
#include <stdlib.h> /* exit(), EXIT_FAILURE, EXIT_SUCCESS */
#include <fcntl.h> /* open(), O_RDONLY */
#include <sys/stat.h> /* fstat() */
#include <unistd.h> /* write() */
#include <sys/mman.h> /* mmap() */

#define INPUT_FILE_ARG_IDX 1

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

	/* Open received input file for reading and writing */
	int fd = open(argv[INPUT_FILE_ARG_IDX], O_RDWR);
	if (fd == -1)
		unix_error("Failed to open file");

	/* Get file size */
	struct stat sb;
	if (fstat(fd, &sb) == -1)
		unix_error("Failed to get size of input file");

	/* Read file contents and create a write-only memory mapping */
	void *start = NULL; /* Let kernel decide */
	off_t offset = 0; /* Start of file */
	char *bufp;

	void *p = mmap(start, sb.st_size, PROT_WRITE, MAP_PRIVATE, fd, offset);
	if (p == MAP_FAILED)
		unix_error("Failed to memory map input file");
	bufp = (char *) p;

	/* Modify file contents */
	*bufp = 'J';
	if (write(fd, bufp, sb.st_size) == -1)
		unix_error("Failed to modify contents of file");

	/* Unmap the region */
	if (munmap(p, sb.st_size) == -1)
		unix_error("Failed to unmap region of input file");

	/* Close file */
	if (close(fd) == -1)
		unix_error("Error closing file");
	exit(EXIT_SUCCESS);
}
