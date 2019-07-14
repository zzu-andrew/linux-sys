#include	"unpipc.h"

int
main(int argc, char **argv)
{
	if (argc != 2)
		err_quit("usage: mqunlink <name>");

	Mq_unlink(argv[1]);

	exit(0);
}
