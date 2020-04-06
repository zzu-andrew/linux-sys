#include	"unpipc.h"

#define	MAXNITEMS 		1000000
#define	MAXNTHREADS			100

		/* globals shared by threads */
int		nitems;				/* read-only by producer and consumer */
int		buff[MAXNITEMS];
struct {
  pthread_mutex_t	mutex;
  pthread_cond_t	cond;
  int				nput;
  int				nval;
  int				nready;
} nready = { PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER };

void	*produce(void *), *consume(void *);

/* include main */
int
main(int argc, char **argv)
{
	int			i, nthreads, count[MAXNTHREADS];
	pthread_t	tid_produce[MAXNTHREADS], tid_consume;

	if (argc != 3)
		err_quit("usage: prodcons5 <#items> <#threads>");
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
		Pthread_mutex_lock(&nready.mutex);
		if (nready.nput >= nitems) {
			Pthread_mutex_unlock(&nready.mutex);
			return(NULL);		/* array is full, we're done */
		}
		buff[nready.nput] = nready.nval;
		nready.nput++;
		nready.nval++;
		nready.nready++;
		Pthread_cond_signal(&nready.cond);
		Pthread_mutex_unlock(&nready.mutex);
		*((int *) arg) += 1;
	}
}

/* include consume */
void *
consume(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		Pthread_mutex_lock(&nready.mutex);
		while (nready.nready == 0)
			Pthread_cond_wait(&nready.cond, &nready.mutex);
		nready.nready--;
		Pthread_mutex_unlock(&nready.mutex);

		if (buff[i] != i)
			printf("buff[%d] = %d\n", i, buff[i]);
	}
	return(NULL);
}
/* end consume */
