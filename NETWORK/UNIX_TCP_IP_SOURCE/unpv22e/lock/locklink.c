#include	"unpipc.h"

#define	LOCKFILE	"/tmp/seqno.lock"
#define	PREFIX		"/tmp"		/* prefix for temp pathname */

void
my_lock(int fd)
{
	char	*ptr;

	ptr = tempnam(PREFIX, NULL);
		/* create/open and then close */
	Close(Open(ptr, O_CREAT | O_RDWR | O_TRUNC, FILE_MODE));

	while (link(ptr, LOCKFILE) < 0) {
		if (errno != EEXIST)
			err_sys("link error for lock file");
		/* someone else has the lock, loop around and try again */
	}
	Unlink(ptr);			/* linked the file, we have the lock */
	free(ptr);				/* tempnam() calls malloc() */
}

void
my_unlock(int fd)
{
	Unlink(LOCKFILE);		/* release lock by removing file */
}
