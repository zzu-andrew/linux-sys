#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		msqid1, msqid2;

	msqid1 = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
	msqid2 = Msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
	printf("msqid1 = %d, msgqid2 = %d\n", msqid1, msqid2);

	exit(0);
}
