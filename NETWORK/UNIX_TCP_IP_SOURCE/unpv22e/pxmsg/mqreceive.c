#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;
	ssize_t	n;
	uint_t	prio;
	void	*buff;
	struct mq_attr	attr;

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

	mqd = Mq_open(argv[optind], flags);
	Mq_getattr(mqd, &attr);

	buff = Malloc(attr.mq_msgsize);

	n = Mq_receive(mqd, buff, attr.mq_msgsize, &prio);
	printf("read %ld bytes, priority = %u\n", (long) n, prio);

	exit(0);
}
