#include	"svmsg.h"

void	client(int, int);

int
main(int argc, char **argv)
{
	int		msqid;

		/* 4server must create the queue */
	msqid = Msgget(MQ_KEY1, 0);

	client(msqid, msqid);	/* same queue for both directions */

	exit(0);
}
