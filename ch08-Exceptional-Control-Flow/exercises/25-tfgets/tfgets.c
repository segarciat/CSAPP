#include <stdio.h> /* fgets(), FILE, NULL */
#include <signal.h> /* struct sigaction, sigaction(), sig_atomic_t, SIGALRM */
#include <errno.h> /* errno */
#include <unistd.h> /* alarm() */

#define TIMEOUT 5

static volatile sig_atomic_t interrupted = 0;

void
sigAlarmHandler(int sig)
{
	interrupted = 1;
}

char *tfgets(char *s, int size, FILE *stream)
{
	/* Install handler */
	struct sigaction sa, oldsa;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigAlarmHandler;
	if (sigaction(SIGALRM, &sa, &oldsa) == -1)
		return NULL;

	/* Schedule SIGALRM and get input */
	alarm(TIMEOUT);
	char *r = fgets(s, size, stream);

	/* Remove alarm if still pending */
	int savedErrno = errno;
	alarm(0);
	errno = savedErrno;

	/* Restore handler */
	if (sigaction(SIGALRM, &oldsa, NULL) == -1)
		return NULL;
	
	return (interrupted) ? NULL: r;
}
