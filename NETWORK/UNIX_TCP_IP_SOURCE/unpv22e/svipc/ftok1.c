#include	"unpipc.h"

int
main(int argc, char **argv)
{
	struct stat	stat;

	if (argc != 2)
		err_quit("usage: ftok1 <pathname>");

	Stat(argv[1], &stat);
	printf("%x %s\n", Ftok(argv[1], 0x57), argv[1]);

	exit(0);
}
