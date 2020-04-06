/* include mq_receive1 */
#include	"unpipc.h"
#include	"mqueue.h"

ssize_t
mymq_receive(mymqd_t mqd, char *ptr, size_t maxlen, unsigned int *priop)
{
	int		n;
	long	index;
	int8_t	*mptr;
	ssize_t	len;
	struct mymq_hdr	*mqhdr;
	struct mymq_attr	*attr;
	struct mymsg_hdr	*msghdr;
	struct mymq_info	*mqinfo;

	mqinfo = mqd;
	if (mqinfo->mqi_magic != MQI_MAGIC) {
		errno = EBADF;
		return(-1);
	}
	mqhdr = mqinfo->mqi_hdr;	/* struct pointer */
	mptr = (int8_t *) mqhdr;	/* byte pointer */
	attr = &mqhdr->mqh_attr;
	if ( (n = pthread_mutex_lock(&mqhdr->mqh_lock)) != 0) {
		errno = n;
		return(-1);
	}

	if (maxlen < attr->mq_msgsize) {
		errno = EMSGSIZE;
		goto err;
	}
	if (attr->mq_curmsgs == 0) {		/* queue is empty */
		if (mqinfo->mqi_flags & O_NONBLOCK) {
			errno = EAGAIN;
			goto err;
		}
			/* 4wait for a message to be placed onto queue */
		mqhdr->mqh_nwait++;
		while (attr->mq_curmsgs == 0)
			pthread_cond_wait(&mqhdr->mqh_wait, &mqhdr->mqh_lock);
		mqhdr->mqh_nwait--;
	}
/* end mq_receive1 */
/* include mq_receive2 */

	if ( (index = mqhdr->mqh_head) == 0)
		err_dump("mymq_receive: curmsgs = %ld; head = 0", attr->mq_curmsgs);

	msghdr = (struct mymsg_hdr *) &mptr[index];
	mqhdr->mqh_head = msghdr->msg_next;	/* new head of list */
	len = msghdr->msg_len;
	memcpy(ptr, msghdr + 1, len);		/* copy the message itself */
	if (priop != NULL)
		*priop = msghdr->msg_prio;

		/* 4just-read message goes to front of free list */
	msghdr->msg_next = mqhdr->mqh_free;
	mqhdr->mqh_free = index;

		/* 4wake up anyone blocked in mq_send waiting for room */
	if (attr->mq_curmsgs == attr->mq_maxmsg)
		pthread_cond_signal(&mqhdr->mqh_wait);
	attr->mq_curmsgs--;

	pthread_mutex_unlock(&mqhdr->mqh_lock);
	return(len);

err:
	pthread_mutex_unlock(&mqhdr->mqh_lock);
	return(-1);
}
/* end mq_receive2 */

ssize_t
Mymq_receive(mymqd_t mqd, char *ptr, size_t len, unsigned int *priop)
{
	ssize_t	n;

	if ( (n = mymq_receive(mqd, ptr, len, priop)) == -1)
		err_sys("mymq_receive error");
	return(n);
}
