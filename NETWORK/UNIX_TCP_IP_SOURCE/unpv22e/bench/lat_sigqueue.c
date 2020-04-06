#include	"unpipc.h"

#ifdef	HAVE_SIGWAIT	/* following should have been in lib/wrapunix.c */
int
Sigwaitinfo(const sigset_t *set, siginfo_t *info)
{
	int		signo;

	if ( (signo = sigwaitinfo(set, info)) != -1)
		return (signo);
	err_sys("sigwaitinfo error, pid = %ld", (long) getpid());
}
#endif

int
main(int argc, char **argv)
{
	int		i, nloop;
	pid_t	childpid, parentpid;
	sigset_t	newmask;
	siginfo_t	siginfo;
	union sigval	val;

	if (argc != 2)
		err_quit("usage: lat_sigqueue <#loops>");
	nloop = atoi(argv[1]);

	Sigemptyset(&newmask);
	Sigaddset(&newmask, SIGRTMIN);
	Sigprocmask(SIG_BLOCK, &newmask, NULL);		/* block SIGRTMIN */

	parentpid = getpid();
	val.sival_int = 0;
	if ( (childpid = Fork()) == 0) {
		for (i = 0; i < nloop; i++) {		/* child */
			Sigwaitinfo(&newmask, &siginfo);
			Sigqueue(parentpid, SIGRTMIN, val);
		}
		exit(0);
	}
		/* 4parent */
	Start_time();
	for (i = 0; i < nloop; i++) {
		Sigqueue(childpid, SIGRTMIN, val);
		Sigwaitinfo(&newmask, &siginfo);
	}
	printf("latency: %.3f usec\n", Stop_time() / nloop);
	exit(0);
}
