/* include mq_open1 */
#include	"unpipc.h"
#include	"mqueue.h"

#include	<stdarg.h>
#define		MAX_TRIES	10	/* for waiting for initialization */

struct mymq_attr	defattr = { 0, 128, 1024, 0 };

mymqd_t
mymq_open(const char *pathname, int oflag, ...)
{
	int		i, fd, nonblock, created, save_errno;
	long	msgsize, filesize, index;
	va_list	ap;
	mode_t	mode;
	int8_t	*mptr;
	struct stat	statbuff;
	struct mymq_hdr	*mqhdr;
	struct mymsg_hdr	*msghdr;
	struct mymq_attr	*attr;
	struct mymq_info	*mqinfo;
	pthread_mutexattr_t	mattr;
	pthread_condattr_t	cattr;

	created = 0;
	nonblock = oflag & O_NONBLOCK;
	oflag &= ~O_NONBLOCK;
	mptr = (int8_t *) MAP_FAILED;
	mqinfo = NULL;
again:
	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t) & ~S_IXUSR;
		attr = va_arg(ap, struct mymq_attr *);
		va_end(ap);

			/* 4open and specify O_EXCL and user-execute */
		fd = open(pathname, oflag | O_EXCL | O_RDWR, mode | S_IXUSR);
		if (fd < 0) {
			if (errno == EEXIST && (oflag & O_EXCL) == 0)
				goto exists;		/* already exists, OK */
			else
				return((mymqd_t) -1);
		}
		created = 1;
			/* 4first one to create the file initializes it */
		if (attr == NULL)
			attr = &defattr;
		else {
			if (attr->mq_maxmsg <= 0 || attr->mq_msgsize <= 0) {
				errno = EINVAL;
				goto err;
			}
		}
/* end mq_open1 */
/* include mq_open2 */
			/* 4calculate and set the file size */
		msgsize = MSGSIZE(attr->mq_msgsize);
		filesize = sizeof(struct mymq_hdr) + (attr->mq_maxmsg *
				   (sizeof(struct mymsg_hdr) + msgsize));
		if (lseek(fd, filesize - 1, SEEK_SET) == -1)
			goto err;
		if (write(fd, "", 1) == -1)
			goto err;

			/* 4memory map the file */
		mptr = mmap(NULL, filesize, PROT_READ | PROT_WRITE,
					MAP_SHARED, fd, 0);
		if (mptr == MAP_FAILED)
			goto err;

			/* 4allocate one mymq_info{} for the queue */
/* *INDENT-OFF* */
		if ( (mqinfo = malloc(sizeof(struct mymq_info))) == NULL)
			goto err;
/* *INDENT-ON* */
		mqinfo->mqi_hdr = mqhdr = (struct mymq_hdr *) mptr;
		mqinfo->mqi_magic = MQI_MAGIC;
		mqinfo->mqi_flags = nonblock;

			/* 4initialize header at beginning of file */
			/* 4create free list with all messages on it */
		mqhdr->mqh_attr.mq_flags = 0;
		mqhdr->mqh_attr.mq_maxmsg = attr->mq_maxmsg;
		mqhdr->mqh_attr.mq_msgsize = attr->mq_msgsize;
		mqhdr->mqh_attr.mq_curmsgs = 0;
		mqhdr->mqh_nwait = 0;
		mqhdr->mqh_pid = 0;
		mqhdr->mqh_head = 0;
		index = sizeof(struct mymq_hdr);
		mqhdr->mqh_free = index;
		for (i = 0; i < attr->mq_maxmsg - 1; i++) {
			msghdr = (struct mymsg_hdr *) &mptr[index];
			index += sizeof(struct mymsg_hdr) + msgsize;
			msghdr->msg_next = index;
		}
		msghdr = (struct mymsg_hdr *) &mptr[index];
		msghdr->msg_next = 0;		/* end of free list */

			/* 4initialize mutex & condition variable */
		if ( (i = pthread_mutexattr_init(&mattr)) != 0)
			goto pthreaderr;
		pthread_mutexattr_setpshared(&mattr, PTHREAD_PROCESS_SHARED);
		i = pthread_mutex_init(&mqhdr->mqh_lock, &mattr);
		pthread_mutexattr_destroy(&mattr);	/* be sure to destroy */
		if (i != 0)
			goto pthreaderr;

		if ( (i = pthread_condattr_init(&cattr)) != 0)
			goto pthreaderr;
		pthread_condattr_setpshared(&cattr, PTHREAD_PROCESS_SHARED);
		i = pthread_cond_init(&mqhdr->mqh_wait, &cattr);
		pthread_condattr_destroy(&cattr);	/* be sure to destroy */
		if (i != 0)
			goto pthreaderr;

			/* 4initialization complete, turn off user-execute bit */
		if (fchmod(fd, mode) == -1)
			goto err;
		close(fd);
		return((mymqd_t) mqinfo);
	}
/* end mq_open2 */
/* include mq_open3 */
exists:
		/* 4open the file then memory map */
	if ( (fd = open(pathname, O_RDWR)) < 0) {
		if (errno == ENOENT && (oflag & O_CREAT))
			goto again;
		goto err;
	}

		/* 4make certain initialization is complete */
	for (i = 0; i < MAX_TRIES; i++) {
		if (stat(pathname, &statbuff) == -1) {
			if (errno == ENOENT && (oflag & O_CREAT)) {
				close(fd);
				goto again;
			}
			goto err;
		}
		if ((statbuff.st_mode & S_IXUSR) == 0)
			break;
		sleep(1);
	}
	if (i == MAX_TRIES) {
		errno = ETIMEDOUT;
		goto err;
	}

	filesize = statbuff.st_size;
	mptr = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (mptr == MAP_FAILED)
		goto err;
	close(fd);

		/* 4allocate one mymq_info{} for each open */
/* *INDENT-OFF* */
	if ( (mqinfo = malloc(sizeof(struct mymq_info))) == NULL)
		goto err;
/* *INDENT-ON* */
	mqinfo->mqi_hdr = (struct mymq_hdr *) mptr;
	mqinfo->mqi_magic = MQI_MAGIC;
	mqinfo->mqi_flags = nonblock;
	return((mymqd_t) mqinfo);
/* $$.bp$$ */
pthreaderr:
	errno = i;
err:
		/* 4don't let following function calls change errno */
	save_errno = errno;
	if (created)
		unlink(pathname);
	if (mptr != MAP_FAILED)
		munmap(mptr, filesize);
	if (mqinfo != NULL)
		free(mqinfo);
	close(fd);
	errno = save_errno;
	return((mymqd_t) -1);
}
/* end mq_open3 */

mymqd_t
Mymq_open(const char *pathname, int oflag, ...)
{
	mymqd_t	mqd;
	va_list	ap;
	mode_t	mode;
	struct mymq_attr	*attr;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		attr = va_arg(ap, struct mymq_attr *);
		if ( (mqd = mymq_open(pathname, oflag, mode, attr)) == (mymqd_t) -1)
			err_sys("mymq_open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (mqd = mymq_open(pathname, oflag)) == (mymqd_t) -1)
			err_sys("mymq_open error for %s", pathname);
	}
	return(mqd);
}
