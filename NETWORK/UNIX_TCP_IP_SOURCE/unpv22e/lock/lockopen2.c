#include	"unpipc.h"

#define	LOCKFILE	"/tmp/seqno.lock"

void
my_lock(int fd)
{
	int		tempfd;

		/* create with O_TRUNC and no permission bits */
	while ( (tempfd = open(LOCKFILE, O_CREAT | O_WRONLY | O_TRUNC, 0)) < 0) {
		if (errno != EACCES)
			err_sys("open error for lock file");
		/* someone else has the lock, loop around and try again */
	}
	Close(tempfd);			/* opened the file, we have the lock */
}

void
my_unlock(int fd)
{
	Unlink(LOCKFILE);		/* release lock by removing file */
}
