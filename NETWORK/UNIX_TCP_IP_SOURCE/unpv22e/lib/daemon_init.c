#include	"unpipc.h"
#include	<syslog.h>

#define	MAXFD	64

extern int	daemon_proc;	/* defined in error.c */

void
daemon_init(const char *pname, int facility)
{
	int		i;
	pid_t	pid;

	if ( (pid = Fork()) != 0)
		exit(0);			/* parent terminates */

	/* 41st child continues */
	setsid();				/* become session leader */

	Signal(SIGHUP, SIG_IGN);
	if ( (pid = Fork()) != 0)
		exit(0);			/* 1st child terminates */

	/* 42nd child continues */
	daemon_proc = 1;		/* for our err_XXX() functions */

	chdir("/");				/* change working directory */

	umask(0);				/* clear our file mode creation mask */

	for (i = 0; i < MAXFD; i++)
		close(i);

	openlog(pname, LOG_PID, facility);
}
