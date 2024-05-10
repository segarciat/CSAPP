#include <unistd.h> /* execve */
#include <stdlib.h> /* exit(), EXIT_SUCCESS, EXIT_FAILURE */
#include <stdio.h> /* fprintf(), stderr */

#define LS_PATH "/bin/ls"

/* Runs ls */
int
main(int argc, char *argv[], char *envp[])
{
	if (execve(LS_PATH, argv, envp) == -1) {
		fprintf(stderr, "%s: Failed to exec %s\n", argv[0], LS_PATH);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
