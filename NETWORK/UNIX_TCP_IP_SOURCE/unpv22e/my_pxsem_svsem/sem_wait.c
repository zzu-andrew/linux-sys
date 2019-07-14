/* include sem_wait */
#include	"unpipc.h"
#include	"semaphore.h"

int
mysem_wait(mysem_t *sem)
{
	struct sembuf	op;

	if (sem->sem_magic != SEM_MAGIC) {
		errno = EINVAL;
		return(-1);
	}

	op.sem_num = 0;
	op.sem_op = -1;
	op.sem_flg = 0;
	if (semop(sem->sem_semid, &op, 1) < 0)
		return(-1);
	return(0);
}
/* end sem_wait */

void
Mysem_wait(mysem_t *sem)
{
	if (mysem_wait(sem) == -1)
		err_sys("mysem_wait error");
}
