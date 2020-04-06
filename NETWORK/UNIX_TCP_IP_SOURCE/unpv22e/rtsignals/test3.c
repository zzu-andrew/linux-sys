/*
 * See how many realtime signals we can queue.
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
		Signal_rt(SIGRTMIN, sig_rt);

		sleep(6);		/* let parent send all the signals */

		Sigprocmask(SIG_SETMASK, &oldset, NULL);	/* unblock */
		sleep(3);		/* let all queued signals be delivered */
		exit(0);
	}

	sleep(3);		/* let child block all signals */
		/* 4parent sends signals to child */
	for (j = 0; j <= 1000000; j++) {
		val.sival_int = j;
		Sigqueue(pid, SIGRTMIN, val);		/* this should fail, eventually */
		printf("sent SIGRTMIN (%ld), val = %d\n", (long) SIGRTMIN, j);
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
