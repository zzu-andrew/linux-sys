/* include mymq_receive */
#include	"unpipc.h"
#include	"mymqueue.h"

static int	mymq_recv_wait(struct mymq_hdr *);

ssize_t
mymq_receive(mymqd_t mqd, char *ptr, size_t maxlen, unsigned int *priop)
{
	int		fd, rc;
	long	index;
	int8_t	*mptr;
	ssize_t	len;
	struct mymq_hdr	*mqhdr;
	struct mymq_attr	*attr;
	struct mymsg_hdr	*msghdr;
	struct mymq_info	*mqinfo;

	mqinfo = (struct mymq_info *) mqd;
	if (mqinfo->mqi_magic != MAGIC)
		err_dump("mymq_receive: magic = %x", mqinfo->mqi_magic);

	fd = mqinfo->mqi_fd;
	mqhdr = mqinfo->mqi_hdr;	/* struct pointer */
	mptr = (int8_t *) mqhdr;	/* byte pointer */
	attr = &mqhdr->mqh_attr;
	pthread_mutex_lock(&mqhdr->mqh_lock);

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
		if ( (rc = mymq_recv_wait(mqhdr)) != 0) {
			errno = rc;
			goto err;
		}
	}

	if ( (index = mqhdr->mqh_head) == 0)
		err_dump("mymq_receive: curmsgs = %ld; head = 0", attr->mq_curmsgs);

	msghdr = (struct mymsg_hdr *) &mptr[index];
	mqhdr->mqh_head = msghdr->msg_next;	/* new head of list */
	len = msghdr->msg_len;
	memcpy(ptr, msghdr + 1, len);		/* copy the message itself */
	if (priop != NULL)
		*priop = msghdr->msg_prio;

		/* 4just read message goes to front of free list */
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
/* end mymq_receive */

/* include mymq_recv_wait */
static void	*mymq_wait_thread(void *);
static int	pipefd[2];

static int
mymq_recv_wait(struct mymq_hdr *mqhdr)
{
	int		rc;
	char	c;
	pthread_t	tid;

	if (pipe(pipefd) == -1)
		return(errno);
	if ( (rc = pthread_create(&tid, NULL, mymq_wait_thread, mqhdr)) != 0) {
		close(pipefd[0]);
		close(pipefd[1]);
		return(rc);
	}
		/* 4read returns 0 if queue nonempty, else -1 with errno set */
	if ( (rc = read(pipefd[0], &c, 1)) != 0)
		rc = errno;
	close(pipefd[0]);
	close(pipefd[1]);
	pthread_cancel(tid);	/* must cancel thread if queue still empty */
	return(rc);				/* 0 if queue nonempty, else an errno */
}

static void *
mymq_wait_thread(void *arg)
{
	struct mymq_hdr *mqhdr;
	struct mymq_attr	*attr;

	mqhdr = (struct mymq_hdr *) arg;
	attr = &mqhdr->mqh_attr;
	while (attr->mq_curmsgs == 0)
		pthread_cond_wait(&mqhdr->mqh_wait, &mqhdr->mqh_lock);

	close(pipefd[1]);	/* queue not empty, close write end of pipe */
	return(NULL);
}
/* end mymq_recv_wait */

ssize_t
Mymq_receive(mymqd_t mqd, char *ptr, size_t len, unsigned int *priop)
{
	ssize_t	n;

	if ( (n = mymq_receive(mqd, ptr, len, priop)) == -1)
		err_sys("mymq_receive error");
	return(n);
}
