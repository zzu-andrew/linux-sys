/* include sem_post */
#include	"unpipc.h"
#include	"semaphore.h"

int
mysem_post(mysem_t *sem)
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
	if (sem->sem_count == 0)
		pthread_cond_signal(&sem->sem_cond);
	sem->sem_count++;
	pthread_mutex_unlock(&sem->sem_mutex);
	return(0);
}
/* end sem_post */

void
Mysem_post(mysem_t *sem)
{
	if (mysem_post(sem) == -1)
		err_sys("mysem_post error");
}
