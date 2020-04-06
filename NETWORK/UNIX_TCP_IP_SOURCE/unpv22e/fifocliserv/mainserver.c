#include	"fifo.h"

void	server(int, int);

int
main(int argc, char **argv)
{
	int		readfifo, writefifo, dummyfd, fd;
	char	*ptr, buff[MAXLINE], fifoname[MAXLINE];
	pid_t	pid;
	ssize_t	n;

		/* 4create server's well-known FIFO; OK if already exists */
	if ((mkfifo(SERV_FIFO, FILE_MODE) < 0) && (errno != EEXIST))
		err_sys("can't create %s", SERV_FIFO);

		/* 4open server's well-known FIFO for reading and writing */
	readfifo = Open(SERV_FIFO, O_RDONLY, 0);
	dummyfd = Open(SERV_FIFO, O_WRONLY, 0);		/* never used */

	while ( (n = Readline(readfifo, buff, MAXLINE)) > 0) {
		if (buff[n-1] == '\n')
			n--;			/* delete newline from readline() */
		buff[n] = '\0';		/* null terminate pathname */

		if ( (ptr = strchr(buff, ' ')) == NULL) {
			err_msg("bogus request: %s", buff);
			continue;
		}

		*ptr++ = 0;			/* null terminate PID, ptr = pathname */
		pid = atol(buff);
		snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long) pid);
		if ( (writefifo = open(fifoname, O_WRONLY, 0)) < 0) {
			err_msg("cannot open: %s", fifoname);
			continue;
		}

		if ( (fd = open(ptr, O_RDONLY)) < 0) {
				/* 4error: must tell client */
			snprintf(buff + n, sizeof(buff) - n, ": can't open, %s\n",
					 strerror(errno));
			n = strlen(ptr);
			Write(writefifo, ptr, n);
			Close(writefifo);
	
		} else {
				/* 4open succeeded: copy file to FIFO */
			while ( (n = Read(fd, buff, MAXLINE)) > 0)
				Write(writefifo, buff, n);
			Close(fd);
			Close(writefifo);
		}
	}
}
