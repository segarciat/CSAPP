/*
 * adder.c - a minimal CGI program that adds two numbers together
 */
/* $begin adder */
#include "csapp.h"

int main(void) {
    char *buf, *p;
    char arg1[MAXLINE], arg2[MAXLINE], content[MAXLINE];
    int n1=0, n2=0;

    /* Extract the two arguments */
    if ((buf = getenv("QUERY_STRING")) != NULL) {
		p = strchr(buf, '&');
		*p = '\0';
		strcpy(arg1, buf);
		strcpy(arg2, p+1);

		p = strchr(arg1, '=');
		n1 = atoi(p + 1);

		p = strchr(arg2, '=');
		n2 = atoi(p + 1);
    }

	snprintf(content, MAXLINE,
			"Welcome to add.com: Modified by Sergio"
			"THE Internet addition portal.\r\n<p>"
			"The answer is: %d + %d = %d\r\n<p>"
			"Thanks for visiting!\r\n",
			n1, n2, n1 + n2
	);
  
    /* Generate the HTTP response */
    printf("Connection: close\r\n");
    printf("Content-length: %d\r\n", (int)strlen(content));
    printf("Content-type: text/html\r\n\r\n");
    printf("%s", content);
    fflush(stdout);

    exit(0);
}
/* $end adder */
