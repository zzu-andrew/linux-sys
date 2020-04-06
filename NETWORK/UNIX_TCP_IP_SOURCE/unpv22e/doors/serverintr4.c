/* include servproc */
#include	"unpipc.h"

void
servproc_cleanup(void *arg)
{
	printf("servproc cancelled, thread id %ld\n", pr_thread_id(NULL));
}

void
servproc(void *cookie, char *dataptr, size_t datasize,
		 door_desc_t *descptr, size_t ndesc)
{
	int		oldstate, junk;
	long	arg, result;
	
	Pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	pthread_cleanup_push(servproc_cleanup, NULL);
	sleep(6);
	arg = *((long *) dataptr);
	result = arg * arg;
	pthread_cleanup_pop(0);
	Pthread_setcancelstate(oldstate, &junk);
	Door_return((char *) &result, sizeof(result), NULL, 0);
}
/* end servproc */

int
main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		err_quit("usage: serverintr4 <server-pathname>");

		/* 4create a door descriptor and attach to pathname */
	fd = Door_create(servproc, NULL, 0);

	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_RDWR, FILE_MODE));
	Fattach(fd, argv[1]);

		/* 4servproc() handles all client requests */
	for ( ; ; )
		pause();
}
