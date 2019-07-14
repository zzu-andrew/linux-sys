/* include wrlock */
#include	"unpipc.h"
#include	"pthread_rwlock.h"

int
pthread_rwlock_wrlock(pthread_rwlock_t *rw)
{
	int		result;

	if (rw->rw_magic != RW_MAGIC)
		return(EINVAL);

	if ( (result = pthread_mutex_lock(&rw->rw_mutex)) != 0)
		return(result);

	while (rw->rw_refcount != 0) {
		rw->rw_nwaitwriters++;
		result = pthread_cond_wait(&rw->rw_condwriters, &rw->rw_mutex);
		rw->rw_nwaitwriters--;
		if (result != 0)
			break;
	}
	if (result == 0)
		rw->rw_refcount = -1;

	pthread_mutex_unlock(&rw->rw_mutex);
	return(result);
}
/* end wrlock */

void
Pthread_rwlock_wrlock(pthread_rwlock_t *rw)
{
	int		n;

	if ( (n = pthread_rwlock_wrlock(rw)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_wrlock error");
}
