#include	"unpipc.h"

#define	MAXMSG	(8192 + sizeof(long))

int
main(int argc, char **argv)
{
	int		pipe1[2], pipe2[2], mqid;
	char	c;
	pid_t	childpid;
	fd_set	rset;
	ssize_t	n, nread;
	struct msgbuf	*buff;

	if (argc != 2)
		err_quit("usage: svmsgread <pathname>");

	Pipe(pipe1);			/* 2-way communication with child */
	Pipe(pipe2);

	buff = My_shm(MAXMSG);	/* anonymous shared memory with child */

	if ( (childpid = Fork()) == 0) {
		Close(pipe1[1]);			/* child */
		Close(pipe2[0]);

		mqid = Msgget(Ftok(argv[1], 0), MSG_R);
		for ( ; ; ) {
				/* 4block, waiting for message, then tell parent */
			nread = Msgrcv(mqid, buff, MAXMSG, 0, 0);
			Write(pipe2[1], &nread, sizeof(ssize_t));

				/* 4wait for parent to say shm is available */
			if ( (n = Read(pipe1[0], &c, 1)) != 1)
				err_quit("child: read on pipe returned %d", n);
		}
		exit(0);
	}
/* $$.bp$$ */
		/* 4parent */
	Close(pipe1[0]);
	Close(pipe2[1]);

	FD_ZERO(&rset);
	FD_SET(pipe2[0], &rset);
	for ( ; ; ) {
		if ( (n = select(pipe2[0] + 1, &rset, NULL, NULL, NULL)) != 1)
			err_sys("select returned %d", n);
		if (FD_ISSET(pipe2[0], &rset)) {
			n = Read(pipe2[0], &nread, sizeof(ssize_t));
/* *INDENT-OFF* */
			if (n != sizeof(ssize_t))
				err_quit("parent: read on pipe returned %d", n);
/* *INDENT-ON* */
			printf("read %d bytes, type = %ld\n", nread, buff->mtype);
			Write(pipe1[1], &c, 1);

		} else
			err_quit("pipe2[0] not ready");
	}

	Kill(childpid, SIGTERM);
	exit(0);
}
