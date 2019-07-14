/* include servproc */
#include	"unpipc.h"

void
servproc(void *cookie, char *dataptr, size_t datasize,
		 door_desc_t *descptr, size_t ndesc)
{
	long	arg, result;
	
	arg = *((long *) dataptr);
	printf("thread id %ld, arg = %ld\n", pr_thread_id(NULL), arg);
	sleep(5);

	result = arg * arg;
	Door_return((char *) &result, sizeof(result), NULL, 0);
}
/* end servproc */

/* include my_thread */
pthread_mutex_t	fdlock = PTHREAD_MUTEX_INITIALIZER;
static int	fd = -1;		/* door descriptor */

void *
my_thread(void *arg)
{
	int		oldstate;
	door_info_t	*iptr = arg;

	if ((Door_server_proc *) iptr->di_proc == servproc) {
		Pthread_mutex_lock(&fdlock);
		Pthread_mutex_unlock(&fdlock);

		Pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
		Door_bind(fd);
		Door_return(NULL, 0, NULL, 0);
	} else
		err_quit("my_thread: unknown function: %p", arg);
	return(NULL);	/* never executed */
}

void
my_create(door_info_t *iptr)
{
	pthread_t	tid;
	pthread_attr_t	attr;

	Pthread_attr_init(&attr);
	Pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	Pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	Pthread_create(&tid, &attr, my_thread, (void *) iptr);
	Pthread_attr_destroy(&attr);
	printf("my_thread: created server thread %ld\n", pr_thread_id(&tid));
}
/* end my_thread */

/* include main */
int
main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("usage: server6 <server-pathname>");

	Door_server_create(my_create);

		/* 4create a door descriptor and attach to pathname */
	Pthread_mutex_lock(&fdlock);
	fd = Door_create(servproc, NULL, DOOR_PRIVATE);
	Pthread_mutex_unlock(&fdlock);

	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_RDWR, FILE_MODE));
	Fattach(fd, argv[1]);

		/* 4servproc() handles all client requests */
	for ( ; ; )
		pause();
}
/* end main */
