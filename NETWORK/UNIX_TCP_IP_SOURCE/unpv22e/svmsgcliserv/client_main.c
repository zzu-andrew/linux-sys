#include	"svmsg.h"

void	client(int, int);

int
main(int argc, char **argv)
{
	int		readid, writeid;

		/* 4assumes server has created the queues */
	writeid = Msgget(MQ_KEY1, 0);
	readid = Msgget(MQ_KEY2, 0);

	client(readid, writeid);

		/* 4now we can delete the queues */
	Msgctl(readid, IPC_RMID, NULL);
	Msgctl(writeid, IPC_RMID, NULL);

	exit(0);
}
