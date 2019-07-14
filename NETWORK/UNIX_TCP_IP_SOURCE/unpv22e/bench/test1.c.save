/* Solaris 2.6:
   gcc -g -O2 -D_REENTRANT -Wall -D__EXTENSIONS__ test1.c -lposix4 -lpthread */
/* Digital Unix 4.0B:
   cc -g -D_REENTRANT test1.c -lrt -lpthread */

#include	<sys/types.h>
#include	<errno.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<unistd.h>
#include	<pthread.h>
#include	<semaphore.h>

#define	MAXNTHREADS	100
#define	min(a,b)	((a) < (b) ? (a) : (b))

int		nloop;

struct {
  sem_t	mutex;		/* the memory-based semaphore */
  long	counter;
} shared;

void	*incr(void *), err_quit(char *);

int
main(int argc, char **argv)
{
	int		i, nthreads;
	pthread_t	tid[MAXNTHREADS];

	if (argc != 3)
		err_quit("usage: incr_pxsem1 <#loops> <#threads>");
	nloop = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

		/* initialize memory-based semaphore to 0 */
	if (sem_init(&shared.mutex, 0, 0) == -1)
		err_quit("sem_init error");

		/* create all the threads */
	for (i = 0; i < nthreads; i++) {
		if (pthread_create(&tid[i], NULL, incr, NULL) != 0)
			err_quit("pthread_create error");
	}
		/* release the semaphore */
	if (sem_post(&shared.mutex) == -1)
		err_quit("sem_post error");

		/* wait for all the threads */
	for (i = 0; i < nthreads; i++) {
		if (pthread_join(tid[i], NULL) != 0)
			err_quit("pthread_join error");
	}
	if (shared.counter != nloop * nthreads)
		printf("error: counter = %ld\n", shared.counter);

	exit(0);
}

void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		if (sem_wait(&shared.mutex) == -1)
			err_quit("sem_wait error");
		shared.counter++;
		if (sem_post(&shared.mutex) == -1)
			err_quit("sem_post error");
	}
	return(NULL);
}

void
err_quit(char *ptr)
{
	fprintf(stderr, "%s\n", ptr);
	exit(1);
}
