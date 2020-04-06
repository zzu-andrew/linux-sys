#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		semid;

	if (argc != 2)
		err_quit("usage: semrmid <pathname>");

	semid = Semget(Ftok(argv[1], 0), 0, 0);
	Semctl(semid, 0, IPC_RMID);

	exit(0);
}
