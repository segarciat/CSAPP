#include <unistd.h> /* sleep() */
#include <stdio.h> /* printf() */
#include "snooze.h"

unsigned int
snooze(unsigned int secs)
{
	unsigned int remaining = sleep(secs);
	printf("Slept for %d of %d secs\n", secs - remaining, secs);
	return remaining;
}
