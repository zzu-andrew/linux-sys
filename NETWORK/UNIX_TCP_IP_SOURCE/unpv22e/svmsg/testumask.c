#include	"unpipc.h"

int
main(int argc, char **argv)
{
	Msgget(IPC_PRIVATE, 0666 | IPC_CREAT | IPC_EXCL);
	unlink("/tmp/fifo.1");
	Mkfifo("/tmp/fifo.1", 0666);

	exit(0);
}
