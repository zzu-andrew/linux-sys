/* include sem_close */
#include	"unpipc.h"
#include	"semaphore.h"

int
mysem_close(mysem_t *sem)
{
	if (sem->sem_magic != SEM_MAGIC) {
		errno = EINVAL;
		return(-1);
	}

	sem->sem_magic = 0;		/* in case caller tries to use it later */
	if (close(sem->sem_fd[0]) == -1 || close(sem->sem_fd[1]) == -1) {
		free(sem);
		return(-1);
	}
	free(sem);
	return(0);
}
/* end sem_close */

void
Mysem_close(mysem_t *sem)
{
	if (mysem_close(sem) == -1)
		err_sys("mysem_close error");
}

