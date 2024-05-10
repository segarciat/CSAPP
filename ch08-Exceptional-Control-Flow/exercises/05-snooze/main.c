#include <stdio.h> /* stderr, fprintf(), printf() */
#include <stdlib.h> /* exit(), EXIT_FAILURE, EXIT_SUCCESS, strtol() */
#include "snooze.h" /* snooze() */

#define DEFAULT_SLEEP 5

/* Parse duration command-line argument */
unsigned int parseDuration(char *arg)
{
#define ANY_BASE 0
	char *endp;
	long duration = strtol(arg, &endp, ANY_BASE);
	if (*endp != '\0') {
		fprintf(stderr, "Invalid character while parsing duration %s: %s\n", arg, endp);
		exit(EXIT_FAILURE);
	}
	/* Unchecked: parsed sleep may be very large */
	if (duration <= 0) {
		fprintf(stderr, "Invalid sleep duration: %ld\n", duration);
		exit(EXIT_FAILURE);
	}
	/* Truncate if too large */
	printf("Parsed duration as %u\n", (unsigned int) duration);
	return (unsigned int) duration;
}

#define DURATION_ARG 1

/* Snooze for the specified number of time, or the default duration */
int
main(int argc, char *argv[])
{
	unsigned duration;

	if (argc > 2) {
		fprintf(stderr, "Usage: %s [duration]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	duration = (argc > 1) ? parseDuration(argv[DURATION_ARG]) : DEFAULT_SLEEP;
	printf("Sleeping for %u seconds...\n", duration);
	snooze(duration);

	exit(EXIT_SUCCESS);
}
