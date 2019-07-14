#include	"unpipc.h"

static int		counter, nloop;
static pid_t	childpid, parentpid;

void
sig_usr1(int signo)
{
	Kill(parentpid, SIGUSR2);		/* child receives USR1, sends USR2 */
	return;
}

void
sig_usr2(int signo)
{
	if (++counter < nloop)
		Kill(childpid, SIGUSR1);	/* parent receives USR2, sends USR1 */
	else
		Kill(parentpid, SIGTERM);	/* parent terminates below */
	return;
}

void
sig_term(int signo)
{
	printf("latency: %.3f usec\n", Stop_time() / nloop);
	Kill(childpid, SIGTERM);
	exit(0);
}

int
main(int argc, char **argv)
{

	if (argc != 2)
		err_quit("usage: lat_signal <#loops>");
	nloop = atoi(argv[1]);
	counter = 0;

	parentpid = getpid();
	Signal(SIGUSR1, sig_usr1);		/* for child */
	Signal(SIGUSR2, sig_usr2);		/* for parent */
	if ( (childpid = Fork()) == 0) {
		for ( ; ; ) {		/* child */
			pause();
		}
		exit(0);	/* never reached */
	}
		/* 4parent */
	Signal(SIGTERM, sig_term);		/* for parent only */
	Start_time();
	Kill(childpid, SIGUSR1);
	for ( ; ; )
		pause();
}
