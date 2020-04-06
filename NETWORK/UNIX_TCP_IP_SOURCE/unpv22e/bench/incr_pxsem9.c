/* Copied from incr_pxsem5.c, but does *not* store sem_t itself in shared
 * memory, to see if a memory-based semaphore is copied across a fork() */
/* include main */
#include	"unpipc.h"

#define	MAXNPROC	100

int		nloop;

struct shared {
  long	counter;
} *shared;		/* actual structure is stored in shared memory */

sem_t	mutex;	/* global that is copied across the fork() */

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nprocs;
	pid_t	childpid[MAXNPROC];

	if (argc != 3)
		err_quit("usage: incr_pxsem9 <#loops> <#processes>");
	nloop = atoi(argv[1]);
	nprocs = min(atoi(argv[2]), MAXNPROC);

		/* 4get shared memory for parent and children */
	shared = My_shm(sizeof(struct shared));

		/* 4initialize memory-based semaphore to 0 */
	Sem_init(&mutex, 1, 0);

		/* 4create all the children */
	for (i = 0; i < nprocs; i++) {
		if ( (childpid[i] = Fork()) == 0) {
			incr(NULL);
			exit(0);
		}
	}
		/* 4parent: start the timer and release the semaphore */
	Start_time();
	Sem_post(&mutex);

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
		Sem_wait(&mutex);
		shared->counter++;
		Sem_post(&mutex);
	}
	return(NULL);
}
/* end incr */
