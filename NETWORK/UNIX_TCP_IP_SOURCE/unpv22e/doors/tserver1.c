#include	"unpipc.h"

void
server(void *cookie, char *argp, size_t arg_size,
	   door_desc_t *dp, size_t n_descriptors)
{
	long	*arg, result[4];
	door_cred_t	info;
	
	if (argp == DOOR_UNREF_DATA) {
		printf("door unreferenced\n");
		Door_return(NULL, 0, NULL, 0);
	}

	printf("server called, thread id %ld, %d bytes of arguments, cookie = %p\n",
		   pr_thread_id(NULL), arg_size, cookie);
sleep(3);
	Door_cred(&info);
	printf("euid = %ld, ruid = %ld, pid = %ld\n",
		   (long) info.dc_euid, (long) info.dc_ruid, (long) info.dc_pid);

	arg = (long *) argp;
	printf("arg[0] = %ld, arg[1] = %ld, arg[2] = %ld, arg[3]= %ld\n\n",
			arg[0], arg[1], arg[2], arg[3]);

	result[0] = arg[0] * arg[0];
	result[1] = arg[1] * arg[1];
	result[2] = arg[2] * arg[2];
	result[3] = arg[3] * arg[3];
	Door_return((char *) result, sizeof(result), NULL, 0);
}

static int	fd = -1;

void *
my_thread(void *arg)
{
	int		oldstate;

	if (arg == server) {
		while (fd == -1)
			thr_yield();

		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &oldstate);
		Door_bind(fd);
		Door_return(NULL, 0, NULL, 0);
	} else
		err_quit("my_thread: unknown function");
	return(NULL);	/* never executed */
}

void
my_create(door_info_t *iptr)
{
	pthread_t	tid;
	pthread_attr_t	attr;

printf("tserver1: iptr = %p\n", iptr);
	Pthread_attr_init(&attr);
	Pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
	Pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	Pthread_create(&tid, &attr, my_thread, (void *) iptr->di_proc);
	Pthread_attr_destroy(&attr);
	printf("created server thread %ld\n", pr_thread_id(&tid));
}

int
main(int argc, char **argv)
{
	struct stat	stat;

	if (argc != 2)
		err_quit("usage: server1 <pathname>");

	Door_server_create(my_create);

		/* 4create a door descriptor */
	fd = Door_create(server, (void *) 44, DOOR_PRIVATE);
	Fstat(fd, &stat);
	printf("server() at %p, fmt = %lx\n", server,
		   (long) stat.st_mode & S_IFMT);

		/* 4bind it to the specified pathname */
	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE));
	Fattach(fd, argv[1]);
	/* Close(fd); */

		/* server() handles all client requests */
	for ( ; ; )
		pause();
}
