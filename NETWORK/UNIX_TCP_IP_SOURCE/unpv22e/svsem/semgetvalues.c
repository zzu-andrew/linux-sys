#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		semid, nsems, i;
	struct semid_ds	seminfo;
	unsigned short	*ptr;
	union semun	arg;

	if (argc != 2)
		err_quit("usage: semgetvalues <pathname>");

		/* 4first get the number of semaphores in the set */
	semid = Semget(Ftok(argv[1], 0), 0, 0);
	arg.buf = &seminfo;
	Semctl(semid, 0, IPC_STAT, arg);
	nsems = arg.buf->sem_nsems;

		/* 4allocate memory to hold all the values in the set */
	ptr = Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;

		/* 4fetch the values and print */
	Semctl(semid, 0, GETALL, arg);
	for (i = 0; i < nsems; i++)
		printf("semval[%d] = %d\n", i, ptr[i]);

	exit(0);
}
