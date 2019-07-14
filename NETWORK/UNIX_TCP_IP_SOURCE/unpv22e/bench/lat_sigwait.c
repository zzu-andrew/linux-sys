#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		i, nloop, signo;
	pid_t	childpid, parentpid;
	sigset_t	newmask;

	if (argc != 2)
		err_quit("usage: lat_sigwait <#loops>");
	nloop = atoi(argv[1]);

	Sigemptyset(&newmask);
	Sigaddset(&newmask, SIGUSR1);
	Sigprocmask(SIG_BLOCK, &newmask, NULL);		/* block SIGUSR1 */

	parentpid = getpid();
	if ( (childpid = Fork()) == 0) {
		for (i = 0; i < nloop; i++) {		/* child */
			Sigwait(&newmask, &signo);
			Kill(parentpid, SIGUSR1);
		}
		exit(0);
	}
		/* 4parent */
	Start_time();
	for (i = 0; i < nloop; i++) {
		Kill(childpid, SIGUSR1);
		Sigwait(&newmask, &signo);
	}
	printf("latency: %.3f usec\n", Stop_time() / nloop);
	exit(0);
}
