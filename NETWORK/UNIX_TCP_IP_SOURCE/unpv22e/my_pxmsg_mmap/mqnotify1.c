#include	"unpipc.h"
#include	"mqueue.h"

mymqd_t	mqd;
struct sigevent	sigev;

void	sig_usr1(int);

int
main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("usage: mqnotify1 <name>");

	mqd = Mymq_open(argv[1], O_RDONLY);

	Signal(SIGUSR1, sig_usr1);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = SIGUSR1;
	Mymq_notify(mqd, &sigev);

	for ( ; ; )
		pause();

	exit(0);
}

void
sig_usr1(int signo)
{
	printf("SIGUSR1 received\n");
	Mymq_notify(mqd, &sigev);			/* reregister */
	return;
}
