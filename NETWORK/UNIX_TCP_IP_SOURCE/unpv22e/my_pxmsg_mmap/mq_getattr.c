/* include mq_getattr */
#include	"unpipc.h"
#include	"mqueue.h"

int
mymq_getattr(mymqd_t mqd, struct mymq_attr *mqstat)
{
	int		n;
	struct mymq_hdr	*mqhdr;
	struct mymq_attr	*attr;
	struct mymq_info	*mqinfo;

	mqinfo = mqd;
	if (mqinfo->mqi_magic != MQI_MAGIC) {
		errno = EBADF;
		return(-1);
	}
	mqhdr = mqinfo->mqi_hdr;
	attr = &mqhdr->mqh_attr;
	if ( (n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0) {
		errno = n;
		return(-1);
	}

	mqstat->mq_flags = mqinfo->mqi_flags;	/* per-open */
	mqstat->mq_maxmsg = attr->mq_maxmsg;	/* remaining three per-queue */
	mqstat->mq_msgsize = attr->mq_msgsize;
	mqstat->mq_curmsgs = attr->mq_curmsgs;

	pthread_mutex_unlock(&mqhdr->mqh_lock);
	return(0);
}
/* end mq_getattr */

void
Mymq_getattr(mymqd_t mqd, struct mymq_attr *mqstat)
{
	if (mymq_getattr(mqd, mqstat) == -1)
		err_sys("mymq_getattr error");
}
