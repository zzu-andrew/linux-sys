#include	"unpipc.h"

volatile sig_atomic_t	caught_sigchld;

void
sig_chld(int signo)
{
	caught_sigchld = 1;
	return;		/* just interrupt door_call() */
}

int
main(int argc, char **argv)
{
	int		fd, rc;
	long	ival, oval;
	door_arg_t	arg;

	if (argc != 3)
		err_quit("usage: clientintr3 <server-pathname> <integer-value>");

	fd = Open(argv[1], O_RDWR);		/* open the door */

		/* 4set up the arguments and pointer to result */
	ival = atol(argv[2]);
	arg.data_ptr = (char *) &ival;	/* data arguments */
	arg.data_size = sizeof(long);	/* size of data arguments */
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *) &oval;		/* data results */
	arg.rsize = sizeof(long);		/* size of data results */

	Signal(SIGCHLD, sig_chld);
	if (Fork() == 0) {
		sleep(2);		/* child */
		exit(0);		/* generates SIGCHLD */	
	}

		/* 4parent: call server procedure and print result */
	for ( ; ; ) {
		printf("calling door_call\n");
		if ( (rc = door_call(fd, &arg)) == 0)
			break;		/* success */
		if (errno == EINTR && caught_sigchld) {
			caught_sigchld = 0;
			continue;	/* call door_call() again */
		}
		err_sys("door_call error");
	}
	printf("result: %ld\n", oval);

	exit(0);
}
