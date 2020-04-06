/* include bw_pxmsg1 */
#include	"unpipc.h"
#define	NAME	"bw_pxmsg"

void	reader(int, mqd_t, int);
void	writer(int, mqd_t);

void	*buf;
int		totalnbytes, xfersize;

int
main(int argc, char **argv)
{
	int		i, nloop, contpipe[2];
	mqd_t	mq;
	pid_t	childpid;
	struct mq_attr	attr;

	if (argc != 4)
		err_quit("usage: bw_pxmsg <#loops> <#mbytes> <#bytes/write>");
	nloop = atoi(argv[1]);
	totalnbytes = atoi(argv[2]) * 1024 * 1024;
	xfersize = atoi(argv[3]);

	buf = Valloc(xfersize);
	Touch(buf, xfersize);

	Pipe(contpipe);
	mq_unlink(Px_ipc_name(NAME));	/* error OK */
	attr.mq_maxmsg = 4;
	attr.mq_msgsize = xfersize;
	mq = Mq_open(Px_ipc_name(NAME), O_RDWR | O_CREAT, FILE_MODE, &attr);

	if ( (childpid = Fork()) == 0) {
		writer(contpipe[0], mq);		/* child */
		exit(0);
	}
		/* 4parent */
	Start_time();
	for (i = 0; i < nloop; i++)
		reader(contpipe[1], mq, totalnbytes);
	printf("bandwidth: %.3f MB/sec\n",
		   totalnbytes / Stop_time() * nloop);

	kill(childpid, SIGTERM);
	Mq_close(mq);
	Mq_unlink(Px_ipc_name(NAME));
	exit(0);
}
/* end bw_pxmsg1 */

/* include bw_pxmsg2 */
void
writer(int contfd, mqd_t mqsend)
{
	int		ntowrite;

	for ( ; ; ) {
		Read(contfd, &ntowrite, sizeof(ntowrite));

		while (ntowrite > 0) {
			Mq_send(mqsend, buf, xfersize, 0);
			ntowrite -= xfersize;
		}
	}
}

void
reader(int contfd, mqd_t mqrecv, int nbytes)
{
	ssize_t	n;

	Write(contfd, &nbytes, sizeof(nbytes));

	while ((nbytes > 0) &&
		   ( (n = Mq_receive(mqrecv, buf, xfersize, NULL)) > 0)) {
		nbytes -= n;
	}
}
/* end bw_pxmsg2 */
