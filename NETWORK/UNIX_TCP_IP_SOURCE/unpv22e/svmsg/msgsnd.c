#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		mqid;
	size_t	len;
	long	type;
	struct msgbuf	*ptr;

	if (argc != 4)
		err_quit("usage: msgsnd <pathname> <#bytes> <type>");
	len = atoi(argv[2]);
	type = atoi(argv[3]);

	mqid = Msgget(Ftok(argv[1], 0), MSG_W);

	ptr = Calloc(sizeof(long) + len, sizeof(char));
	ptr->mtype = type;

	Msgsnd(mqid, ptr, len, 0);

	exit(0);
}
