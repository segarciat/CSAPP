#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* waitpid() */
#include <unistd.h> /* execve(), fork() */
#include <stdio.h> /* fprintf(), stderr */
#include <stdlib.h> /* exit(), EXIT_FAILURE */
#include <string.h> /* strerror() */
#include <errno.h> /* errno */
#include <alloca.h>
#include "mysystem.h"

#define SHELL_PATH "/bin/sh"

extern char **environ;

void error(char *msg)
{
	fprintf(stderr, "%s: %s\n", msg, strerror(errno));
	exit(EXIT_FAILURE);
}

int mysystem(char *command)
{
	pid_t pid;
	int status;
	char *args[4] = { SHELL_PATH, "-c", command, NULL};
	switch(pid = fork()) {
		case -1: /* Failure */
			error("Fork failed");
			break;
		case  0: /* Child */
			if (execve(SHELL_PATH, args, environ) == -1)
				error("exec failed");
			break;
		default: /* Parent */
			if (waitpid(pid, &status, 0) == -1)
				error("waitpid failed");
			if (WIFEXITED(status))
				return WEXITSTATUS(status);
			break;
	}
	return -1;
}
