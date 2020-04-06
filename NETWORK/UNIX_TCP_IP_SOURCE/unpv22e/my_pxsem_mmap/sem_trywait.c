/* include sem_trywait */
#include	"unpipc.h"
#include	"semaphore.h"

int
mysem_trywait(mysem_t *sem)
{
	int		n, rc;

	if (sem->sem_magic != SEM_MAGIC) {
		errno = EINVAL;
		return(-1);
	}

	if ( (n = pthread_mutex_lock(&sem->sem_mutex)) != 0) {
		errno = n;
		return(-1);
	}
	if (sem->sem_count > 0) {
		sem->sem_count--;
		rc = 0;
	} else {
		rc = -1;
		errno = EAGAIN;
	}
	pthread_mutex_unlock(&sem->sem_mutex);
	return(rc);
}
/* end sem_trywait */

int
Mysem_trywait(mysem_t *sem)
{
	int		rc;

	if ( (rc = mysem_trywait(sem)) == -1 && errno != EAGAIN)
		err_sys("mysem_trywait error");
	return(rc);
}
