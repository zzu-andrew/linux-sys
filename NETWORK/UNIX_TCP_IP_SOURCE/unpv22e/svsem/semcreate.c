#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		c, oflag, semid, nsems;

	oflag = SVSEM_MODE | IPC_CREAT;
	while ( (c = Getopt(argc, argv, "e")) != -1) {
		switch (c) {
		case 'e':
			oflag |= IPC_EXCL;
			break;
		}
	}
	if (optind != argc - 2)
		err_quit("usage: semcreate [ -e ] <pathname> <nsems>");
	nsems = atoi(argv[optind + 1]);

	semid = Semget(Ftok(argv[optind], 0), nsems, oflag);
	exit(0);
}
