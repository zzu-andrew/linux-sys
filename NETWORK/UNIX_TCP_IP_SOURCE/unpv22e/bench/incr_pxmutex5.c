/* include main */
#include	"unpipc.h"

#define	MAXNPROC	100

int		nloop;

struct shared {
  pthread_mutex_t	mutex;
  long	counter;
} *shared;		/* pointer; actual structure in shared memory */

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nprocs;
	pid_t	childpid[MAXNPROC];
	pthread_mutexattr_t	mattr;

	if (argc != 3)
		err_quit("usage: incr_pxmutex5 <#loops> <#processes>");
	nloop = atoi(argv[1]);
	nprocs = min(atoi(argv[2]), MAXNPROC);

		/* 4get shared memory for parent and children */
	shared = My_shm(sizeof(struct shared));

		/* 4initialize the mutex and lock it */
	Pthread_mutexattr_init(&mattr);
	Pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
	Pthread_mutex_init(&shared->mutex, &mattr);
	Pthread_mutexattr_destroy(&mattr);
	Pthread_mutex_lock(&shared->mutex);

		/* 4create all the children */
	for (i = 0; i < nprocs; i++) {
		if ( (childpid[i] = Fork()) == 0) {
			incr(NULL);
			exit(0);
		}
	}
		/* 4parent: start the timer and unlock the mutex */
	Start_time();
	Pthread_mutex_unlock(&shared->mutex);

		/* 4wait for all the children */
	for (i = 0; i < nprocs; i++) {
		Waitpid(childpid[i], NULL, 0);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared->counter != nloop * nprocs)
		printf("error: counter = %ld\n", shared->counter);

	exit(0);
}
/* end main */

/* include incr */
void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		Pthread_mutex_lock(&shared->mutex);
		shared->counter++;
		Pthread_mutex_unlock(&shared->mutex);
	}
	return(NULL);
}
/* end incr */
