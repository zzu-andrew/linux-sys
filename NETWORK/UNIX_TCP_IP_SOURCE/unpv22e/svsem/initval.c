#include	"unpipc.h"

#define	NSEMS	10		/* #semaphores in set */

int
main(int argc, char **argv)
{
	int		semid, i, j;
	unsigned short	*ptr;
	union semun	arg;

		/* 4allocate memory to hold all the values in the set */
	ptr = Calloc(NSEMS, sizeof(unsigned short));
	arg.array = ptr;

	for (j = 0; j < 1000; j++) {
			/* 4create a semaphore set */
		semid = Semget(100, NSEMS, IPC_CREAT | IPC_EXCL | SVSEM_MODE);

			/* 4fetch the "initial" values and print */
		Semctl(semid, 0, GETALL, arg);
		for (i = 0; i < NSEMS; i++)
			printf("semval[%d] = %d\n", i, ptr[i]);

			/* 4store new values for entire set */
		for (i = 0; i < NSEMS; i++)
			ptr[i] = rand();
		Semctl(semid, 0, SETALL, arg);

			/* 4and delete the set */
		Semctl(semid, 0, IPC_RMID);
	}

	exit(0);
}
