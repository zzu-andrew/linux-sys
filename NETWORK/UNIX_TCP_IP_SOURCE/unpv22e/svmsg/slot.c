#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		i, msqid;

	for (i = 0; i < 10; i++) {
		msqid = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
		printf("msqid = %d\n", msqid);

		Msgctl(msqid, IPC_RMID, NULL);
	}
	exit(0);
}
