#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "memset.h"

static double timeApproach(void* (*memset)(void *buf, int c, size_t n), void *buf, int c, int n, size_t trials, char *msg)
{
	if (trials == 0)
		return 0.0;
	
	double elapsed = 0.0;
	/* Clear buf */
	unsigned char *unscbuf = (unsigned char *) buf;
	for (size_t i = 0; i < trials; i++) {
		for (int i = 0; i < n; i++)
			unscbuf[i] = 0;

		/* Time memset */
		clock_t start, end;
		if ((start = clock()) == -1) {
			fprintf(stderr, "Could not get start time\n");
			exit(EXIT_FAILURE);
		}
		memset(buf, c, n);
		if ((end = clock()) == -1) {
			fprintf(stderr, "Could not get end time\n");
			exit(EXIT_FAILURE);
		}
		elapsed += (double) (end - start) / CLOCKS_PER_SEC;
	}
	double average = elapsed / trials;
	printf("%s: %.8f\n", msg == NULL ? "time" : msg, average);
	return average;
}

int
main(int argc, char *argv[])
{
	/* Small test case for manual verification */
	size_t n = 16;
	int c = 0x4FE2;
	char smallbuf[n];

	unsigned char *result = (unsigned char *) memset_improved((void*) smallbuf, c, n);
	// unsigned char *result = (unsigned char *) basic_memset((void*) smallbuff, c, n);
	for (size_t i = 0; i < n; i++)
		printf("Byte: %.2x\n", result[i]);
	printf("\n");

	/* Compare performance of approaches */
	size_t m = 2000000;
	size_t trials = 20;
	char buf[m];
	double tbasic = timeApproach(basic_memset, buf, c, m, trials, "basic_memset");
	double timproved = timeApproach(memset_improved, buf, c, m, trials, "memset_improved");
	printf("Improved was about %f times faster\n", tbasic / timproved);
}
