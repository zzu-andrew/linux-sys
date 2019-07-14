/* include main */
#include	"unpipc.h"

#define	MAXNTHREADS	100

int		nloop;

struct {
  int	semid;
  long	counter;
} shared;

struct sembuf	postop, waitop;

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nthreads;
	pthread_t	tid[MAXNTHREADS];
	union semun	arg;

	if (argc != 3)
		err_quit("usage: incr_svsem2 <#loops> <#threads>");
	nloop = atoi(argv[1]);
	nthreads = min(atoi(argv[2]), MAXNTHREADS);

		/* 4create semaphore and initialize to 0 */
	shared.semid = Semget(IPC_PRIVATE, 1, IPC_CREAT | SVSEM_MODE);
	arg.val = 0;
	Semctl(shared.semid, 0, SETVAL, arg);
	postop.sem_num = 0;		/* and init the two semop() structures */
	postop.sem_op  = 1;
	postop.sem_flg = SEM_UNDO;
	waitop.sem_num = 0;
	waitop.sem_op  = -1;
	waitop.sem_flg = SEM_UNDO;

		/* 4create all the threads */
	Set_concurrency(nthreads);
	for (i = 0; i < nthreads; i++) {
		Pthread_create(&tid[i], NULL, incr, NULL);
	}
		/* 4start the timer and release the semaphore */
	Start_time();
	Semop(shared.semid, &postop, 1);		/* up by 1 */

		/* 4wait for all the threads */
	for (i = 0; i < nthreads; i++) {
		Pthread_join(tid[i], NULL);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared.counter != nloop * nthreads)
		printf("error: counter = %ld\n", shared.counter);
	Semctl(shared.semid, 0, IPC_RMID);

	exit(0);
}
/* end main */

/* include incr */
void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		Semop(shared.semid, &waitop, 1);
		shared.counter++;
		Semop(shared.semid, &postop, 1);
	}
	return(NULL);
}
/* end incr */
