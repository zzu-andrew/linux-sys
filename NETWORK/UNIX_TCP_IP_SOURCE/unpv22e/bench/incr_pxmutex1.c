/* include main */
#include	"unpipc.h"

#define	MAXNTHREADS	100

int		nloop;

struct {
  pthread_mutex_t	mutex;
  long	counter;
} shared = { PTHREAD_MUTEX_INITIALIZER };

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nthreads;
	pthread_t	tid[MAXNTHREADS];

	if (argc != 3)
		err_quit("usage: incr_pxmutex1 <#loops> <#threads>");
	nloop = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

		/* 4lock the mutex */
	Pthread_mutex_lock(&shared.mutex);

		/* 4create all the threads */
	Set_concurrency(nthreads);
	for (i = 0; i < nthreads; i++) {
		Pthread_create(&tid[i], NULL, incr, NULL);
	}
		/* 4start the timer and unlock the mutex */
	Start_time();
	Pthread_mutex_unlock(&shared.mutex);

		/* 4wait for all the threads */
	for (i = 0; i < nthreads; i++) {
		Pthread_join(tid[i], NULL);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared.counter != nloop * nthreads)
		printf("error: counter = %ld\n", shared.counter);

	exit(0);
}
/* end main */

/* include incr */
void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		Pthread_mutex_lock(&shared.mutex);
		shared.counter++;
		Pthread_mutex_unlock(&shared.mutex);
	}
	return(NULL);
}
/* end incr */
