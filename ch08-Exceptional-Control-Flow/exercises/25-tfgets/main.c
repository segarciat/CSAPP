#include <stdio.h>
#include "tfgets.h"

int
main()
{
	char buf[BUFSIZ];
	tfgets(buf, BUFSIZ, stdin);
	puts(buf);
	return 0;
}
