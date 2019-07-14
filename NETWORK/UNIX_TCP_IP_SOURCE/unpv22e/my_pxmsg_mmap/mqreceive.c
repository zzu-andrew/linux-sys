#include	"unpipc.h"
#include	"mqueue.h"

int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;
	size_t	n;
	uint_t	prio;
	void	*buff;
	struct mymq_attr	attr;

	flags = O_RDONLY;
	while ( (c = Getopt(argc, argv, "n")) != -1) {
		switch (c) {
		case 'n':
			flags |= O_NONBLOCK;
			break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage: mqreceive [ -n ] <name>");

	mqd = Mymq_open(argv[optind], flags);
	Mymq_getattr(mqd, &attr);

	buff = Malloc(attr.mq_msgsize);

	n = Mymq_receive(mqd, buff, attr.mq_msgsize, &prio);
	printf("read %d bytes, priority = %u\n", n, prio);

	exit(0);
}
