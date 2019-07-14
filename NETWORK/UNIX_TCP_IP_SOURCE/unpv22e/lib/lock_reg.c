/* include lock_reg */
#include	"unpipc.h"

int
lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	struct flock	lock;

	lock.l_type = type;		/* F_RDLCK, F_WRLCK, F_UNLCK */
	lock.l_start = offset;	/* byte offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	return( fcntl(fd, cmd, &lock) );	/* -1 upon error */
}
/* end lock_reg */

void
Lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
	if (lock_reg(fd, cmd, type, offset, whence, len) == -1)
		err_sys("lock_reg error");
}
