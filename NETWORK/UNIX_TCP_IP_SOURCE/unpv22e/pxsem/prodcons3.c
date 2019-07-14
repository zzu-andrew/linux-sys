/* include main */
#include	"unpipc.h"

#define	NBUFF	 	 10
#define	MAXNTHREADS	100

int		nitems, nproducers;		/* read-only by producer and consumer */

struct {	/* data shared by producers and consumer */
  int	buff[NBUFF];
  int	nput;
  int	nputval;
  sem_t	mutex, nempty, nstored;		/* semaphores, not pointers */
} shared;

void	*produce(void *), *consume(void *);

int
main(int argc, char **argv)
{
	int		i, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("usage: prodcons3 <#items> <#producers>");
	nitems = atoi(argv[1]);
	nproducers = min(atoi(argv[2]), MAXNTHREADS);

		/* 4initialize three semaphores */
	Sem_init(&shared.mutex, 0, 1);
	Sem_init(&shared.nempty, 0, NBUFF);
	Sem_init(&shared.nstored, 0, 0);

		/* 4create all producers and one consumer */
	Set_concurrency(nproducers + 1);
	for (i = 0; i < nproducers; i++) {
		count[i] = 0;
		Pthread_create(&tid_produce[i], NULL, produce, &count[i]);
	}
	Pthread_create(&tid_consume, NULL, consume, NULL);

		/* 4wait for all producers and the consumer */
	for (i = 0; i < nproducers; i++) {
		Pthread_join(tid_produce[i], NULL);
		printf("count[%d] = %d\n", i, count[i]);	
	}
	Pthread_join(tid_consume, NULL);

	Sem_destroy(&shared.mutex);
	Sem_destroy(&shared.nempty);
	Sem_destroy(&shared.nstored);
	exit(0);
}
/* end main */

/* include produce */
void *
produce(void *arg)
{
	for ( ; ; ) {
		Sem_wait(&shared.nempty);	/* wait for at least 1 empty slot */
		Sem_wait(&shared.mutex);

		if (shared.nput >= nitems) {
			Sem_post(&shared.nempty);
			Sem_post(&shared.mutex);
			return(NULL);			/* all done */
		}

		shared.buff[shared.nput % NBUFF] = shared.nputval;
		shared.nput++;
		shared.nputval++;

		Sem_post(&shared.mutex);
		Sem_post(&shared.nstored);	/* 1 more stored item */
		*((int *) arg) += 1;
	}
}
/* end produce */

/* include consume */
void *
consume(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		Sem_wait(&shared.nstored);		/* wait for at least 1 stored item */
		Sem_wait(&shared.mutex);

		if (shared.buff[i % NBUFF] != i)
			printf("error: buff[%d] = %d\n", i, shared.buff[i % NBUFF]);

		Sem_post(&shared.mutex);
		Sem_post(&shared.nempty);		/* 1 more empty slot */
	}
	return(NULL);
}
/* end consume */
