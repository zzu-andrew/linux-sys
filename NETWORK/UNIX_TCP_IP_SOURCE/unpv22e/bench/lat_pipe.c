/* include lat_pipe1 */
#include	"unpipc.h"

void
doit(int readfd, int writefd)
{
	char	c;

	Write(writefd, &c, 1);
	if (Read(readfd, &c, 1) != 1)
		err_quit("read error");
}

int
main(int argc, char **argv)
{
	int		i, nloop, pipe1[2], pipe2[2];
	char	c;
	pid_t	childpid;

	if (argc != 2)
		err_quit("usage: lat_pipe <#loops>");
	nloop = atoi(argv[1]);

	Pipe(pipe1);
	Pipe(pipe2);

	if ( (childpid = Fork()) == 0) {
		for ( ; ; ) {		/* child */
			if (Read(pipe1[0], &c, 1) != 1)
				err_quit("read error");
		    Write(pipe2[1], &c, 1);
		}
		exit(0);
	}
		/* 4parent */
	doit(pipe2[0], pipe1[1]);

	Start_time();
	for (i = 0; i < nloop; i++)
		doit(pipe2[0], pipe1[1]);
	printf("latency: %.3f usec\n", Stop_time() / nloop);

	Kill(childpid, SIGTERM);
	exit(0);
}
/* end lat_pipe1 */
