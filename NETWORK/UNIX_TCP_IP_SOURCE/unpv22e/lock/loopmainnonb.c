#include	"unpipc.h"

#define	SEQFILE	"seqno"		/* filename */

void	my_lock(int), my_unlock(int);

int
main(int argc, char **argv)
{
	int		fd;
	long	i, nloop, seqno;
	ssize_t	n;
	char	line[MAXLINE + 1];

	if (argc != 2)
		err_quit("usage: loopmain <loopcount>");
	nloop = atol(argv[1]);

	fd = Open(SEQFILE, O_RDWR | O_NONBLOCK, FILE_MODE);

	for (i = 0; i < nloop; i++) {
		my_lock(fd);				/* lock the file */

		Lseek(fd, 0L, SEEK_SET);	/* rewind before read */
		n = Read(fd, line, MAXLINE);
		line[n] = '\0';				/* null terminate for sscanf */

		n = sscanf(line, "%ld\n", &seqno);
		seqno++;					/* increment sequence number */

		snprintf(line, sizeof(line), "%ld\n", seqno);
		Lseek(fd, 0L, SEEK_SET);	/* rewind before write */
		Write(fd, line, strlen(line));

		my_unlock(fd);				/* unlock the file */
	}
	exit(0);
}
