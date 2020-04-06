#include	"unpipc.h"

#define	MYSIG_NOTIFY	(SIGRTMIN+2)

struct sigevent	sigev;

static Sigfunc_rt	sig_notify;

int
main(int argc, char **argv)
{
	mqd_t	mqd;

	if (argc != 2)
		err_quit("usage: mqnotify3 <name>");

	mqd = Mq_open(argv[1], O_RDONLY);

	Signal_rt(MYSIG_NOTIFY, sig_notify);

	sigev.sigev_notify = SIGEV_SIGNAL;
	sigev.sigev_signo = MYSIG_NOTIFY;
	sigev.sigev_value.sival_ptr = &mqd;
	Mq_notify(mqd, &sigev);

	for ( ; ; )
		pause();		/* signal handler does everything */

	exit(0);
}

static void
sig_notify(int signo, siginfo_t *info, void *context)
{
	printf("MYSIG_NOTIFY received\n");
	if (info->si_code != SI_MESGQ)
		err_quit("si_code = %d", info->si_code);
	Mq_notify(*((mqd_t *) info->si_value.sival_ptr), &sigev);
	return;
}
