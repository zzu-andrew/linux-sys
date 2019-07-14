/* include lat_pxmsg1 */
#include	"unpipc.h"
#define	NAME1	"lat_pxmsg1"
#define	NAME2	"lat_pxmsg2"
#define	MAXMSG	   4		/* room for 4096 bytes on queue */
#define	MSGSIZE	1024

void
doit(mqd_t mqsend, mqd_t mqrecv)
{
	char	buff[MSGSIZE];

	Mq_send(mqsend, buff, 1, 0);
	if (Mq_receive(mqrecv, buff, MSGSIZE, NULL) != 1)
		err_quit("mq_receive error");
}

int
main(int argc, char **argv)
{
	int		i, nloop;
	mqd_t	mq1, mq2;
	char	buff[MSGSIZE];
	pid_t	childpid;
	struct mq_attr	attr;

	if (argc != 2)
		err_quit("usage: lat_pxmsg <#loops>");
	nloop = atoi(argv[1]);

	attr.mq_maxmsg = MAXMSG;
	attr.mq_msgsize = MSGSIZE;
	mq1 = Mq_open(Px_ipc_name(NAME1), O_RDWR | O_CREAT, FILE_MODE, &attr);
	mq2 = Mq_open(Px_ipc_name(NAME2), O_RDWR | O_CREAT, FILE_MODE, &attr);

	if ( (childpid = Fork()) == 0) {
		for ( ; ; ) {			/* child */
			if (Mq_receive(mq1, buff, MSGSIZE, NULL) != 1)
				err_quit("mq_receive error");
		    Mq_send(mq2, buff, 1, 0);
		}
		exit(0);
	}
		/* 4parent */
	doit(mq1, mq2);

	Start_time();
	for (i = 0; i < nloop; i++)
		doit(mq1, mq2);
	printf("latency: %.3f usec\n", Stop_time() / nloop);

	Kill(childpid, SIGTERM);
	Mq_close(mq1);
	Mq_close(mq2);
	Mq_unlink(Px_ipc_name(NAME1));
	Mq_unlink(Px_ipc_name(NAME2));
	exit(0);
}
/* end lat_pxmsg1 */
