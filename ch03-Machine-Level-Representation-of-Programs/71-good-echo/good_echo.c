#include <stdio.h> // stdin stream, fgets, BUFSIZ

/* Reads a line from standard input and writes it to standard output */
void good_echo()
{
	char buf[BUFSIZ];
	while(fgets(buf, BUFSIZ, stdin) != NULL) {
		int numPrinted = printf("%s", buf);
		if (numPrinted < 0 || buf[numPrinted - 1] == '\n')
			break;
	}
}

int main()
{
	good_echo();
}
