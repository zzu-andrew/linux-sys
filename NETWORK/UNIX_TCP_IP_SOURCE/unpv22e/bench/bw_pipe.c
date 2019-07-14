/* include bw_pipe1 */
#include	"unpipc.h"

void	reader(int, int, int);
void	writer(int, int);

void	*buf;
int		totalnbytes, xfersize;

int
main(int argc, char **argv)
{
	int		i, nloop, contpipe[2], datapipe[2];
	pid_t	childpid;

	if (argc != 4)
		err_quit("usage: bw_pipe <#loops> <#mbytes> <#bytes/write>");
	nloop = atoi(argv[1]);
	totalnbytes = atoi(argv[2]) * 1024 * 1024;
	xfersize = atoi(argv[3]);

	buf = Valloc(xfersize);
	Touch(buf, xfersize);

	Pipe(contpipe);
	Pipe(datapipe);

	if ( (childpid = Fork()) == 0) {
		writer(contpipe[0], datapipe[1]);	/* child */
		exit(0);
	}
		/* 4parent */
	Start_time();
	for (i = 0; i < nloop; i++)
		reader(contpipe[1], datapipe[0], totalnbytes);
	printf("bandwidth: %.3f MB/sec\n",
		   totalnbytes / Stop_time() * nloop);
	kill(childpid, SIGTERM);
	exit(0);
}
/* end bw_pipe1 */

/* include bw_pipe2 */
void
writer(int contfd, int datafd)
{
	int		ntowrite;

	for ( ; ; ) {
		Read(contfd, &ntowrite, sizeof(ntowrite));

		while (ntowrite > 0) {
			Write(datafd, buf, xfersize);
			ntowrite -= xfersize;
		}
	}
}

void
reader(int contfd, int datafd, int nbytes)
{
	ssize_t	n;

	Write(contfd, &nbytes, sizeof(nbytes));

	while ((nbytes > 0) &&
		   ( (n = Read(datafd, buf, xfersize)) > 0)) {
		nbytes -= n;
	}
}
/* end bw_pipe2 */
