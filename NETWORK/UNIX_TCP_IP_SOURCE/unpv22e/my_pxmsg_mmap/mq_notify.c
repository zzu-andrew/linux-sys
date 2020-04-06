/* include mq_notify */
#include	"unpipc.h"
#include	"mqueue.h"

int
mymq_notify(mymqd_t mqd, const struct sigevent *notification)
{
	int		n;
	pid_t	pid;
	struct mymq_hdr	*mqhdr;
	struct mymq_info	*mqinfo;

	mqinfo = mqd;
	if (mqinfo->mqi_magic != MQI_MAGIC) {
		errno = EBADF;
		return(-1);
	}
	mqhdr = mqinfo->mqi_hdr;
	if ( (n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0) {
		errno = n;
		return(-1);
	}

	pid = getpid();
	if (notification == NULL) {
		if (mqhdr->mqh_pid == pid) {
			mqhdr->mqh_pid = 0;	/* unregister calling process */
		} 						/* no error if caller not registered */
	} else {
		if (mqhdr->mqh_pid != 0) {
			if (kill(mqhdr->mqh_pid, 0) != -1 || errno != ESRCH) {
				errno = EBUSY;
				goto err;
			}
		}
		mqhdr->mqh_pid = pid;
		mqhdr->mqh_event = *notification;
	}
	pthread_mutex_unlock(&mqhdr->mqh_lock);
	return(0);

err:
	pthread_mutex_unlock(&mqhdr->mqh_lock);
	return(-1);
}
/* end mq_notify */

void
Mymq_notify(mymqd_t mqd, const struct sigevent *notification)
{
	if (mymq_notify(mqd, notification) == -1)
		err_sys("mymq_notify error");
}
