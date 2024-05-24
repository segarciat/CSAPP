#include <stdio.h> /* fprintf(), stderr */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <sys/stat.h> /* stat(), struct stat, S_ISREG(), S_ISDIR(), S_ISSOCK() */
#include <unistd.h>
#include <string.h> /* strerror() */
#include <errno.h> /* errno */

#define FD_ARG_IDX 1

void
unix_error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

int
main(int argc, char *argv[])
{
	/* Ensure we got enough arguments */
	if (argc != 2) {
		fprintf(stderr, "Usage: %s file-descriptor\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* Make sure it's a number */
	char *endp;
	errno = 0;
	int fd = (int) strtol(argv[FD_ARG_IDX], &endp, 0); /* any base */
	if (errno != 0)
		unix_error("Error reading input number");
	else if (*endp != '\0') {
		fprintf(stderr, "%s: Encountered non-numeric character %c in input string %s\n",
			argv[0], *endp, argv[FD_ARG_IDX]);
		exit(EXIT_FAILURE);
	}

	/* Read file metadata */
	struct stat sb;
	if (fstat(fd, &sb) == -1)
		unix_error("Failed to read metadata for input file descriptor");

	/* Determine file type */
	char *type, *readok;
	if (S_ISREG(sb.st_mode))
		type = "regular";
	else if (S_ISDIR(sb.st_mode))
		type = "directory";
	else
		type = "other";
	
	/* Check read access */
	if ((sb.st_mode & S_IRUSR))
		readok = "yes";
	else
		readok = "no";

	/* Display information */
	printf("type: %s, read: %s\n", type, readok);
	exit(EXIT_SUCCESS);
}
