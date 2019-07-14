#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		c, i, flag, semid, nops;
	struct sembuf	*ptr;

	flag = 0;
	while ( (c = Getopt(argc, argv, "nu")) != -1) {
		switch (c) {
		case 'n':
			flag |= IPC_NOWAIT;		/* for each operation */
			break;

		case 'u':
			flag |= SEM_UNDO;		/* for each operation */
			break;
		}
	}
	if (argc - optind < 2)			/* argc - optind = #args remaining */
		err_quit("usage: semops [ -n ] [ -u ] <pathname> operation ...");

	semid = Semget(Ftok(argv[optind], 0), 0, 0);
	optind++;
	nops = argc - optind;

		/* 4allocate memory to hold operations, store, and perform */
	ptr = Calloc(nops, sizeof(struct sembuf));
	for (i = 0; i < nops; i++) {
		ptr[i].sem_num = i;
		ptr[i].sem_op = atoi(argv[optind + i]);	/* <0, 0, or >0 */
		ptr[i].sem_flg = flag;
	}
	Semop(semid, ptr, nops);

	exit(0);
}
