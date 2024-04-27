#include <stdio.h>
#include <time.h> /* srand() */
#include <stdlib.h> /* rand(), RAND_MAX */
#include "evalpoly.h"


double
timeApproach(double (*eval)(double a[], double x, long degree), double a[], double x, long degree, size_t trials, char *msg)
{
	if (trials == 0)
		return -1;
	double total = 0;
	double value;
	for (long i = 0; i < trials; i++) {
		clock_t start, end;
		if ((start = clock()) == -1) {
			fprintf(stderr, "Could not get start time\n");
			exit(EXIT_FAILURE);
		}
		value = eval(a, x, degree);
		if ((end = clock()) == -1) {
			fprintf(stderr, "Could not get end time\n");
			exit(EXIT_FAILURE);
		}
		total += (double) (end - start) / CLOCKS_PER_SEC;
	}

	printf("%s: %.4f\n", msg == NULL ? "time" : msg, total); 
	printf("value = %f\n", value);
	return total / trials;
}


int
main(int argc, char *argv[])
{

	long degree = 10000;
	double a[degree + 1];
	srand(time(NULL));

	/* Initialize coefficients */
	for (size_t i = 0; i <= degree; i++)
		a[i] = 1.0 + ((double)rand() / RAND_MAX);

	double x = 1.03;
	size_t trials = 30;
	/* Evaluate */
	double tpoly = timeApproach(poly, a, x, degree, trials, "poly");
	double tpolyh = timeApproach(polyh, a, x, degree, trials, "polyh");
	double tpoly_roll = timeApproach(poly_roll, a, x, degree, trials, "tpoly_roll");
	double tpoly_rolla = timeApproach(poly_rolla, a, x, degree, trials, "tpoly_rolla");
	/* Compare */
	printf("\n");
	printf("poly shows about a factor %f improvement over polyh \n", tpolyh / tpoly);
	printf("poly_roll shows about a factor %f improvement over poly \n", tpoly / tpoly_roll);
	printf("polyh_rolla shows about a factor %f improvement over poly \n", tpoly / tpoly_rolla);
}
