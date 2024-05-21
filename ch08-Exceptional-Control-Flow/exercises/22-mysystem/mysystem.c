#include <sys/types.h> /* pid_t */
#include <sys/wait.h> /* waitpid() */
#include <unistd.h> /* execve(), fork() */
#include "mysystem.h"

#define SHELL_PATH "/bin/sh"

extern char **environ;

int mysystem(char *command)
{
	pid_t pid;
	int status;
	char *args[4] = { SHELL_PATH, "-c", command, NULL};
	switch(pid = fork()) {
		case -1: /* Failure */
			return -1;
		case  0: /* Child */
			if (execve(SHELL_PATH, args, environ) == -1)
				return -1;
		default: /* Parent */
			if (waitpid(pid, &status, 0) == -1)
				return -1;
			if (WIFEXITED(status))
				return WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				return WSTOPSIG(status);
			return -1;
	}
}
