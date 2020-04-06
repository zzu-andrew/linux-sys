/* include init */
#include	"unpipc.h"
#include	"pthread_rwlock.h"

int
pthread_rwlock_init(pthread_rwlock_t *rw, pthread_rwlockattr_t *attr)
{
	int		result;

	if (attr != NULL)
		return(EINVAL);		/* not supported */

	if ( (result = pthread_mutex_init(&rw->rw_mutex, NULL)) != 0)
		goto err1;
	if ( (result = pthread_cond_init(&rw->rw_condreaders, NULL)) != 0)
		goto err2;
	if ( (result = pthread_cond_init(&rw->rw_condwriters, NULL)) != 0)
		goto err3;
	rw->rw_nwaitreaders = 0;
	rw->rw_nwaitwriters = 0;
	rw->rw_refcount = 0;
	rw->rw_magic = RW_MAGIC;

	return(0);

err3:
	pthread_cond_destroy(&rw->rw_condreaders);
err2:
	pthread_mutex_destroy(&rw->rw_mutex);
err1:
	return(result);			/* an errno value */
}
/* end init */

void
Pthread_rwlock_init(pthread_rwlock_t *rw, pthread_rwlockattr_t *attr)
{
	int		n;

	if ( (n = pthread_rwlock_init(rw, attr)) == 0)
		return;
	errno = n;
	err_sys("pthread_rwlock_init error");
}
