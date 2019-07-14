/* include main */
#include	"unpipc.h"

#define	MAXNPROC	100

int		nloop;

struct shared {
  int	semid;
  long	counter;
} *shared;		/* actual structure is stored in shared memory */

struct sembuf	postop, waitop;

void	*incr(void *);

int
main(int argc, char **argv)
{
	int		i, nprocs;
	pid_t	childpid[MAXNPROC];
	union semun	arg;

	if (argc != 3)
		err_quit("usage: incr_svsem5 <#loops> <#processes>");
	nloop = atoi(argv[1]);
	nprocs = min(atoi(argv[2]), MAXNPROC);

		/* 4get shared memory for parent and children */
	shared = My_shm(sizeof(struct shared));

		/* 4create semaphore and initialize to 0 */
	shared->semid = Semget(IPC_PRIVATE, 1, IPC_CREAT | SVSEM_MODE);
	arg.val = 0;
	Semctl(shared->semid, 0, SETVAL, arg);
	postop.sem_num = 0;		/* and init the two semop() structures */
	postop.sem_op  = 1;
	postop.sem_flg = 0;
	waitop.sem_num = 0;
	waitop.sem_op  = -1;
	waitop.sem_flg = 0;

		/* 4create all the children */
	for (i = 0; i < nprocs; i++) {
		if ( (childpid[i] = Fork()) == 0) {
			incr(NULL);
			exit(0);
		}
	}
		/* 4parent: start the timer and release the semaphore */
	Start_time();
	Semop(shared->semid, &postop, 1);		/* up by 1 */

		/* 4wait for all the children */
	for (i = 0; i < nprocs; i++) {
		Waitpid(childpid[i], NULL, 0);
	}
	printf("microseconds: %.0f usec\n", Stop_time());
	if (shared->counter != nloop * nprocs)
		printf("error: counter = %ld\n", shared->counter);
	Semctl(shared->semid, 0, IPC_RMID);

	exit(0);
}
/* end main */

/* include incr */
void *
incr(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		Semop(shared->semid, &waitop, 1);
		shared->counter++;
		Semop(shared->semid, &postop, 1);
	}
	return(NULL);
}
/* end incr */
