#include "evalpoly.h"

/* Basic polynomial evaluation */
double poly(double a[], double x, long degree)
{
	long i;
	double result = a[0];
	double xpwr = x;
	for (i = 1; i <= degree; i++) {
		result += a[i] * xpwr;
		xpwr = x * xpwr;
	}
	return result;
}

/* Evaluate polynomial using Horner's Method */
double polyh(double a[], double x, long degree)
{
	long i;
	double result = a[degree];
	for (i = degree - 1; i >= 0; i--)
		result = a[i - 1] + x * result;
	return result;
}


/* Evaluate polynomial using k by k loop unrolling */ 
double poly_roll(double a[], double x, long degree)
{
	double x1 = x;
	double x2 = x * x  ;
	double x3 = x2 * x ;
	double x4 = x2 * x2;
	double x5 = x3 * x2;
	double x6 = x3 * x3;
	double x7 = x4 * x3;
	double x8 = x4 * x4;
	double x9 = x5 * x4;
	double x10 = x5 * x5;
	const double xpwr = x10;

	/* Unrolling factor */
	const int k = 10;
	/* i + (k-1) <= degree iff i <= degree - (k-1) */
	const long limit = degree - (k-1);

	double acc1, acc2, acc3, acc4, acc5, acc6, acc7, acc8, acc9, acc10;
	acc1 = a[0];
	acc2 = acc3 = acc4 = acc5 = acc6 = acc7 = acc8 = acc9 = acc10 = 0;


	long i;
	for (i = 1; i <= limit; i += k) {
		acc1 += a[i]   * x1;
		acc2 += a[i+1] * x2;
		acc3 += a[i+2] * x3;
		acc4 += a[i+3] * x4;
		acc5 += a[i+4] * x5;
		acc6 += a[i+5] * x6;
		acc7 += a[i+6] * x7;
		acc8 += a[i+7] * x8;
		acc9 += a[i+8] * x9;
		acc10 += a[i+9] * x10;
		
		x1 *= xpwr;
		x2 *= xpwr;
		x3 *= xpwr;
		x4 *= xpwr;
		x5 *= xpwr;
		x6 *= xpwr;
		x7 *= xpwr;
		x8 *= xpwr;
		x9 *= xpwr;
		x10 *= xpwr;
	}

	/* Finish remaining */
	for (; i <= degree; i++) {
		acc1 += a[i] * x1;
		x1 *= x;
	}
	return acc1 + acc2 + acc3 + acc4 + acc5 + acc6 + acc7 + acc8 + acc9 + acc10; 
}

/* Evaluate polynomial with a mix of factoring (not quite like Horner's though) and unrolling
 * Based on: https://github.com/aben20807/assign_5_18/blob/master/old_reference/poly_funcs_5_5.c#L263
 */
double poly_rolla(double a[], double x,  long degree)
{
	long i;
	double x2 = x * x;
	double x3 = x2 * x;
	double x6 = x3 * x3;
	double x9 = x6 * x3;
	double xpwr = x;
	double result0 = a[0];
	double result1 = 0;
	double result2 = 0;
	int k = 9;
	int limit = degree - (k - 1);
	for (i = 1; i <= limit; i += k) {
		result0 += (a[i    ] + a[i + 1] * x + a[i + 2] * x2) * xpwr;
		result1 += (a[i + 3] + a[i + 4] * x + a[i + 5] * x2) * (xpwr * x3);
		result2 += (a[i + 6] + a[i + 7] * x + a[i + 8] * x2) * (xpwr * x6);
		xpwr *= x9;
	}

	for (; i <= degree; i++) {
		result0 += a[i] * xpwr;
		xpwr *= x;
	}
	return result0 + result1 + result2;
}
