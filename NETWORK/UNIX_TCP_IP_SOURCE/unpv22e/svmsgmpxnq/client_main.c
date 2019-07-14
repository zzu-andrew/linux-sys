#include	"svmsg.h"

void	client(int, int);

int
main(int argc, char **argv)
{
	int		readid, writeid;

		/* 4server must create its well-known queue */
	writeid = Msgget(MQ_KEY1, 0);
		/* 4we create our own private queue */
	readid = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);

	client(readid, writeid);

		/* 4and delete our private queue */
	Msgctl(readid, IPC_RMID, NULL);

	exit(0);
}
