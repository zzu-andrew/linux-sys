#include	"unpipc.h"

#define	PATH_PIDFILE	"pidfile"

int
main(int argc, char **argv)
{
	int		pidfd;
	char	line[MAXLINE];

		/* 4open the PID file, create if nonexistent */
	pidfd = Open(PATH_PIDFILE, O_RDWR | O_CREAT, FILE_MODE);

		/* 4try to write lock the entire file */
	if (write_lock(pidfd, 0, SEEK_SET, 0) < 0) {
		if (errno == EACCES || errno == EAGAIN)
			err_quit("unable to lock %s, is %s already running?",
					 PATH_PIDFILE, argv[0]);
		else
			err_sys("unable to lock %s", PATH_PIDFILE);
	}

		/* 4write my PID, leave file open to hold the write lock */
	snprintf(line, sizeof(line), "%ld\n", (long) getpid());
	Ftruncate(pidfd, 0);
    Write(pidfd, line, strlen(line));

	/* then do whatever the daemon does ... */

	pause();
}
