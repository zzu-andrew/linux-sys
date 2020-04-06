/* include main */
#include	"unpipc.h"
#include	<synch.h>		/* Solaris header */

void	 Rw_wrlock(rwlock_t *rwptr);
void	 Rw_unlock(rwlock_t *rwptr);
void	 Rwlock_init(rwlock_t *rwptr, int type, void *arg);

#define	MAXNPROC	100

int		nloop;

struct shared {
  rwlock_t	rwlock;			/* the Solaris datatype */
  long	counter;
} *shared;		/* actual structure is stored in shared memory */

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nprocs;
	pid_t	childpid[MAXNPROC];

	if (argc != 3)
		err_quit("usage: incr_rwlock5 <#loops> <#processes>");
	nloop = atoi(argv[1]);
	nprocs = min(atoi(argv[2]), MAXNPROC);

		/* 4get shared memory for parent and children */
	shared = My_shm(sizeof(struct shared));

		/* 4initialize the read-write lock and obtain write lock */
	Rwlock_init(&shared->rwlock, USYNC_PROCESS, NULL);
	Rw_wrlock(&shared->rwlock);

		/* 4create all the children */
	for (i = 0; i < nprocs; i++) {
		if ( (childpid[i] = Fork()) == 0) {
			incr(NULL);
			exit(0);
		}
	}
		/* 4parent: start the timer and release the write lock */
	Start_time();
	Rw_unlock(&shared->rwlock);

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
		Rw_wrlock(&shared->rwlock);
		shared->counter++;
		Rw_unlock(&shared->rwlock);
	}
	return(NULL);
}
/* end incr */

void
Rw_wrlock(rwlock_t *rwptr)
{
	int		n;

	if ( (n = rw_wrlock(rwptr)) == 0)
		return;
	errno = n;
	err_sys("rw_wrlock error");
}

void
Rw_unlock(rwlock_t *rwptr)
{
	int		n;

	if ( (n = rw_unlock(rwptr)) == 0)
		return;
	errno = n;
	err_sys("rw_unlock error");
}

void
Rwlock_init(rwlock_t *rwptr, int type, void *arg)
{
	int		n;

	if ( (n = rwlock_init(rwptr, type, arg)) == 0)
		return;
	errno = n;
	err_sys("rwlock_init error");
}
