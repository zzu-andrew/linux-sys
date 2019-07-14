/* include lock_test */
#include	"unpipc.h"

pid_t
lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	struct flock	lock;

	lock.l_type = type;		/* F_RDLCK or F_WRLCK */
	lock.l_start = offset;	/* byte offset, relative to l_whence */
	lock.l_whence = whence;	/* SEEK_SET, SEEK_CUR, SEEK_END */
	lock.l_len = len;		/* #bytes (0 means to EOF) */

	if (fcntl(fd, F_GETLK, &lock) == -1)
		return(-1);			/* unexpected error */

	if (lock.l_type == F_UNLCK)
		return(0);			/* false, region not locked by another proc */
	return(lock.l_pid);		/* true, return positive PID of lock owner */
}
/* end lock_test */

pid_t
Lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
	pid_t	pid;

	if ( (pid = lock_test(fd, type, offset, whence, len)) == -1)
		err_sys("lock_test error");
	return(pid);
}
