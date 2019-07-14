#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		semid, nsems, i;
	struct semid_ds	seminfo;
	unsigned short	*ptr;
	union semun	arg;

	if (argc < 2)
		err_quit("usage: semsetvalues <pathname> [ values ... ]");

		/* 4first get the number of semaphores in the set */
	semid = Semget(Ftok(argv[1], 0), 0, 0);
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;

		/* 4now get the values from the command line */
	if (argc != nsems + 2)
		err_quit("%d semaphores in set, %d values specified", nsems, argc-2);

		/* 4allocate memory to hold all the values in the set, and store */
	ptr = Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;
	for (i = 0; i < nsems; i++)
		ptr[i] = atoi(argv[i + 2]);
	Semctl(semid, 0, SETALL, arg);

	exit(0);
}
