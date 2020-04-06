/* include lat_svmsg1 */
#include	"unpipc.h"

/* *INDENT-OFF* */
struct msgbuf	p2child = { 1, { 0 } };		/* type = 1 */
struct msgbuf	child2p = { 2, { 0 } };		/* type = 2 */
struct msgbuf	inbuf;
/* *INDENT-ON* */

void
doit(int msgid)
{
	Msgsnd(msgid, &p2child, 0, 0);
	if (Msgrcv(msgid, &inbuf, sizeof(inbuf.mtext), 2, 0) != 0)
		err_quit("msgrcv error");
}

int
main(int argc, char **argv)
{
	int		i, nloop, msgid;
	pid_t	childpid;

	if (argc != 2)
		err_quit("usage: lat_svmsg <#loops>");
	nloop = atoi(argv[1]);

	msgid = Msgget(IPC_PRIVATE, IPC_CREAT | SVMSG_MODE);

	if ( (childpid = Fork()) == 0) {
		for ( ; ; ) {		/* child */
			if (Msgrcv(msgid, &inbuf, sizeof(inbuf.mtext), 1, 0) != 0)
				err_quit("msgrcv error");
		    Msgsnd(msgid, &child2p, 0, 0);
		}
		exit(0);
	}
		/* 4parent */
	doit(msgid);

	Start_time();
	for (i = 0; i < nloop; i++)
		doit(msgid);
	printf("latency: %.3f usec\n", Stop_time() / nloop);

	Kill(childpid, SIGTERM);
	Msgctl(msgid, IPC_RMID, NULL);
	exit(0);
}
/* end lat_svmsg1 */
