#include	"unpipc.h"

#define	MAXNPROC	100

int		nloop;

struct shared {
  int	fd;
  long	counter;
} *shared;		/* actual structure is stored in shared memory */

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nprocs;
	char	*pathname;
	pid_t	childpid[MAXNPROC];

	if (argc != 4)
		err_quit("usage: incr_fcntl5 <pathname> <#loops> <#processes>");
	pathname = argv[1];
	nloop = atoi(argv[2]);
	nprocs = min(atoi(argv[3]), MAXNPROC);

		/* 4get shared memory for parent and children */
	shared = My_shm(sizeof(struct shared));

		/* 4create the lock file and obtain a write lock */
	shared->fd = Open(pathname, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
	Writew_lock(shared->fd, 0, SEEK_SET, 0);

		/* 4create all the children */
	for (i = 0; i < nprocs; i++) {
		if ( (childpid[i] = Fork()) == 0) {
			incr(NULL);
			exit(0);
		}
	}
		/* 4parent: start the timer and release the write lock */
	Start_time();
	Un_lock(shared->fd, 0, SEEK_SET, 0);

		/* 4wait for all the children */
	for (i = 0; i < nprocs; i++) {
		Waitpid(childpid[i], NULL, 0);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared->counter != nloop * nprocs)
		printf("error: counter = %ld\n", shared->counter);
	Unlink(pathname);

	exit(0);
}
/* end main */

/* include incr */
void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		Writew_lock(shared->fd, 0, SEEK_SET, 0);
		shared->counter++;
		Un_lock(shared->fd, 0, SEEK_SET, 0);
	}
	return(NULL);
}
/* end incr */
