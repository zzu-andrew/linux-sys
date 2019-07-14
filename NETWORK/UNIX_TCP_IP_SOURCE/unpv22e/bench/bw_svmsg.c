/* include bw_svmsg1 */
#include	"unpipc.h"

void	reader(int, int, int);
void	writer(int, int);

struct msgbuf	*buf;
int		totalnbytes, xfersize;

int
main(int argc, char **argv)
{
	int		i, nloop, contpipe[2], msqid;
	pid_t	childpid;

	if (argc != 4)
		err_quit("usage: bw_svmsg <#loops> <#mbytes> <#bytes/write>");
	nloop = atoi(argv[1]);
	totalnbytes = atoi(argv[2]) * 1024 * 1024;
	xfersize = atoi(argv[3]);

	buf = Valloc(xfersize);
	Touch(buf, xfersize);
	buf->mtype = 1;

	Pipe(contpipe);
	msqid = Msgget(IPC_PRIVATE, IPC_CREAT | SVMSG_MODE);

	if ( (childpid = Fork()) == 0) {
		writer(contpipe[0], msqid);		/* child */
		exit(0);
	}
	Start_time();
	for (i = 0; i < nloop; i++)
		reader(contpipe[1], msqid, totalnbytes);
	printf("bandwidth: %.3f MB/sec\n",
		   totalnbytes / Stop_time() * nloop);

	kill(childpid, SIGTERM);
	Msgctl(msqid, IPC_RMID, NULL);
	exit(0);
}
/* end bw_svmsg1 */

/* include bw_svmsg2 */
void
writer(int contfd, int msqid)
{
	int		ntowrite;

	for ( ; ; ) {
		Read(contfd, &ntowrite, sizeof(ntowrite));

		while (ntowrite > 0) {
			Msgsnd(msqid, buf, xfersize - sizeof(long), 0);
			ntowrite -= xfersize;
		}
	}
}

void
reader(int contfd, int msqid, int nbytes)
{
	ssize_t	n;

	Write(contfd, &nbytes, sizeof(nbytes));

	while ((nbytes > 0) &&
		   ( (n = Msgrcv(msqid, buf, xfersize - sizeof(long), 0, 0)) > 0)) {
		nbytes -= n + sizeof(long);
	}
}
/* end bw_svmsg2 */
