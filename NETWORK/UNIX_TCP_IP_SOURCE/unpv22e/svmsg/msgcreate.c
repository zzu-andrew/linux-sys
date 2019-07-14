#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		c, oflag, mqid;

	oflag = SVMSG_MODE | IPC_CREAT;
	while ( (c = Getopt(argc, argv, "e")) != -1) {
		switch (c) {
		case 'e':
			oflag |= IPC_EXCL;
			break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage: msgcreate [ -e ] <pathname>");

	mqid = Msgget(Ftok(argv[optind], 0), oflag);
	exit(0);
}
