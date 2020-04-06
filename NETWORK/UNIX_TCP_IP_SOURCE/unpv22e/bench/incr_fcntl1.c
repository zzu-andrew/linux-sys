/* Although this program compiles and runs for 1 thread, you cannot run
   it with more than 1 thread, since fcntl locks are between processes,
   not threads */

/* include main */
#include	"unpipc.h"

#define	MAXNTHREADS	100

int		nloop;

struct {
  int	fd;
  long	counter;
} shared;

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nthreads;
	char	*pathname;
	pthread_t	tid[MAXNTHREADS];

	if (argc != 4)
		err_quit("usage: incr_fcntl1 <pathname> <#loops> <#threads>");
	pathname = argv[1];
	nloop = atoi(argv[2]);
	nthreads = min(atoi(argv[3]), MAXNTHREADS);

		/* 4create the file and obtain write lock */
	shared.fd = Open(pathname, O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
	Writew_lock(shared.fd, 0, SEEK_SET, 0);

		/* 4create all the threads */
	Set_concurrency(nthreads);
	for (i = 0; i < nthreads; i++) {
		Pthread_create(&tid[i], NULL, incr, NULL);
	}
		/* 4start the timer and release the write lock */
	Start_time();
	Un_lock(shared.fd, 0, SEEK_SET, 0);

		/* 4wait for all the threads */
	for (i = 0; i < nthreads; i++) {
		Pthread_join(tid[i], NULL);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared.counter != nloop * nthreads)
		printf("error: counter = %ld\n", shared.counter);
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
		Writew_lock(shared.fd, 0, SEEK_SET, 0);
		shared.counter++;
		Un_lock(shared.fd, 0, SEEK_SET, 0);
	}
	return(NULL);
}
/* end incr */
