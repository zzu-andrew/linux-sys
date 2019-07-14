/*
 * See if signals other than the realtime signals are queued,
 * and if SA_SIGINFO works with these other signals.
 */

#include	"unpipc.h"

static void	sig_rt(int, siginfo_t *, void *);

int
main(int argc, char **argv)
{
	int		j;
	pid_t	pid;
	sigset_t	newset, oldset;
	union sigval	val;

	if ( (pid = Fork()) == 0) {
			/* 4block all signals except SIGALRM */
		Sigfillset(&newset);
		Sigdelset(&newset, SIGALRM);
		Sigprocmask(SIG_SETMASK, &newset, &oldset);

			/* establish signal handler with SA_SIGINFO set */
		Signal_rt(SIGUSR1, sig_rt);
		Signal_rt(SIGTERM, sig_rt);

		sleep(6);		/* let parent send all the signals */

		Sigprocmask(SIG_SETMASK, &oldset, NULL);	/* unblock */
		sleep(3);		/* let all queued signals be delivered */
		exit(0);
	}

	sleep(3);		/* let child block all signals */
		/* 4parent sends 12 signals to child */
	for (j = 0; j <= 6; j++) {
		val.sival_int = j;
		Sigqueue(pid, SIGUSR1, val);
		printf("sent SIGUSR1 (%d), val = %d\n", SIGUSR1, j);
	}
	for (j = 0; j <= 6; j++) {
		val.sival_int = j;
		Sigqueue(pid, SIGTERM, val);
		printf("sent SIGTERM (%d), val = %d\n", SIGTERM, j);
	}
	Waitpid(pid, NULL, 0);		/* wait for child */
	exit(0);
}

static void
sig_rt(int signo, siginfo_t *info, void *context)
{
	printf("received signal #%d, code = %d, ival = %d\n",
		   signo, info->si_code, info->si_value.sival_int);
}
