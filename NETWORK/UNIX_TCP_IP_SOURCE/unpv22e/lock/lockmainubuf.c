#include	"unpipc.h"

#define	SEQFILE	"seqno"		/* filename */

void	my_lock(int), my_unlock(int);

int
main(int argc, char **argv)
{
	int		fd, i, seqno, c;
	pid_t	pid;
	ssize_t	n;
	char	line[MAXLINE + 1], *ptr;

	pid = getpid();
	fd = Open(SEQFILE, O_RDWR | O_CREAT, FILE_MODE);

	setvbuf(stdout, NULL, _IONBF, 0);	/* unbuffered */

	for (i = 0; i < 20; i++) {
		my_lock(fd);				/* lock the file */

		Lseek(fd, 0L, SEEK_SET);	/* rewind before read */
		n = Read(fd, line, MAXLINE);
		line[n] = '\0';				/* null terminate for sscanf */

		n = sscanf(line, "%d\n", &seqno);
		snprintf(line, sizeof(line), "pid = %d, seq# = %d\n", pid, seqno);
		for (ptr = line; (c = *ptr++) != 0; )
			putchar(c);

		seqno++;					/* increment sequence number */

		sprintf(line, "%03d\n", seqno);
		Lseek(fd, 0, SEEK_SET);		/* rewind before write */
		Write(fd, line, strlen(line));

		my_unlock(fd);				/* unlock the file */
	}
	exit(0);
}
