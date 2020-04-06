/* include sem_wait */
#include	"unpipc.h"
#include	"semaphore.h"

int
mysem_wait(mysem_t *sem)
{
	int		n;

	if (sem->sem_magic != SEM_MAGIC) {
		errno = EINVAL;
		return(-1);
	}

	if ( (n = pthread_mutex_lock(&sem->sem_mutex)) != 0) {
		errno = n;
		return(-1);
	}
	while (sem->sem_count == 0)
		pthread_cond_wait(&sem->sem_cond, &sem->sem_mutex);
	sem->sem_count--;
	pthread_mutex_unlock(&sem->sem_mutex);
	return(0);
}
/* end sem_wait */

void
Mysem_wait(mysem_t *sem)
{
	if (mysem_wait(sem) == -1)
		err_sys("mysem_wait error");
}
