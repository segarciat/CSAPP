#include <stdio.h> /* printf() */

int
main(int argc, char *argv[], char *envp[])
{
	/* Compute width of argv indices */
	char buf[BUFSIZ];
	int argvIndexWidth = snprintf(buf, BUFSIZ, "%d", argc);

	/* Display command line arguments */
	printf("Command-line arguments\n");
	for (int i = 0; i < argc; i++)
		printf("\targv[%*d]: %s\n", argvIndexWidth, i, argv[i]);
	
	/* Count number of env variables and compute envp index width */
	int envpCount = 0;
	for (char **p = envp; *p != NULL; p++)
		envpCount++;
	int envpIndexWidth = snprintf(buf, BUFSIZ, "%d", envpCount);

	/* Display environment variables */
	printf("Environment variables:\n");
	for (int i = 0; i < envpCount; i++)
		printf("\tenvp[%*d]: %s\n", envpIndexWidth, i, envp[i]);
}
