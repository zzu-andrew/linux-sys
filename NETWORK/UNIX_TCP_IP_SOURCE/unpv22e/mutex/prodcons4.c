#include	"unpipc.h"

#define	MAXNITEMS 		1000000
#define	MAXNTHREADS			100

int		nitems;			/* read-only by producer and consumer */
struct {
  pthread_mutex_t	mutex;
  int	buff[MAXNITEMS];
  int	nput;
  int	nval;
} shared = { PTHREAD_MUTEX_INITIALIZER };

void	*produce(void *), *consume(void *);

/* include main */
int
main(int argc, char **argv)
{
	int			i, nthreads, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("usage: prodcons4 <#items> <#threads>");
	nitems = min(atoi(argv[1]), MAXNITEMS);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

	Set_concurrency(nthreads + 1);
		/* 4create all producers and one consumer */
	for (i = 0; i < nthreads; i++) {
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_consume, NULL, consume, NULL);

		/* wait for all producers and the consumer */
	for (i = 0; i < nthreads; i++) {
		Pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);	
	}
	Pthread_join(tid_consume, NULL);

	exit(0);
}
/* end main */

void *
produce(void *arg)
{
	for ( ; ; ) {
		Pthread_mutex_lock(&shared.mutex);
		if (shared.nput >= nitems) {
			Pthread_mutex_unlock(&shared.mutex);
			return(NULL);		/* array is full, we're done */
		}
		shared.buff[shared.nput] = shared.nval;
		shared.nput++;
		shared.nval++;
		Pthread_mutex_unlock(&shared.mutex);
		*((int *) arg) += 1;
	}
}

/* include consume */
void
consume_wait(int i)
{
	for ( ; ; ) {
		Pthread_mutex_lock(&shared.mutex);
		if (i < shared.nput) {
			Pthread_mutex_unlock(&shared.mutex);
			return;			/* an item is ready */
		}
		Pthread_mutex_unlock(&shared.mutex);
		sched_yield();
	}
}

void *
consume(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		consume_wait(i);
		if (shared.buff[i] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i]);
	}
	return(NULL);
}
/* end consume */
