#include <stdio.h>
// #include <inttypes.h> /* Alternatively, use int64_t and int32_t */


/* Determine whether arguments can be multiplied without overflow
 *
 * Attribution: Implementation from CSAPP 3rd edition, Practice Problem 2.35
 */
int tmult_ok(int x, int y)
{
	int p = x*y;
	/* Either x is zero, or dividing p by x gives y */
	return !x || p/x == y;
}

int
main(int argc, char *argv[])
{
	int n = 1;
	int result = 1;
	while (tmult_ok(result, n)) {
		result *= n;
		printf("%20d\t%20d\n", n, result);
		n++;
	}
}
