/* include main */
#include	"unpipc.h"
#include	<tis.h>		/* Digital Unix header */

void	 Rw_init(tis_rwlock_t *rwptr);
void	 Rw_wrlock(tis_rwlock_t *rwptr);
void	 Rw_unlock(tis_rwlock_t *rwptr);

#define	MAXNTHREADS	100

int		nloop;

struct {
  tis_rwlock_t	rwlock;			/* the DUnix datatype */
  long	counter;
} shared;

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nthreads;
	pthread_t	tid[MAXNTHREADS];

	if (argc != 3)
		err_quit("usage: incr_rwlock2 <#loops> <#threads>");
	nloop = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

		/* 4initialize and obtain write lock */
	Rw_init(&shared.rwlock);
	Rw_wrlock(&shared.rwlock);

		/* 4create all the threads */
	Set_concurrency(nthreads);
	for (i = 0; i < nthreads; i++) {
		Pthread_create(&tid[i], NULL, incr, NULL);
	}
		/* 4start the timer and release the write lock */
	Start_time();
	Rw_unlock(&shared.rwlock);

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
		Rw_wrlock(&shared.rwlock);
		shared.counter++;
		Rw_unlock(&shared.rwlock);
	}
	return(NULL);
}
/* end incr */

void
Rw_init(tis_rwlock_t *rwptr)
{
	int		n;

	if ( (n = tis_rwlock_init(rwptr)) == 0)
		return;
	errno = n;
	err_sys("tis_rwlock_init error");
}

void
Rw_wrlock(tis_rwlock_t *rwptr)
{
	int		n;

	if ( (n = tis_write_lock(rwptr)) == 0)
		return;
	errno = n;
	err_sys("tis_write_lock error");
}

void
Rw_unlock(tis_rwlock_t *rwptr)
{
	int		n;

	if ( (n = tis_write_unlock(rwptr)) == 0)
		return;
	errno = n;
	err_sys("tis_write_unlock error");
}
