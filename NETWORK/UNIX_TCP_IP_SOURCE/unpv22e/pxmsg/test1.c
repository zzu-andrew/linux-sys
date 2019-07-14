#include	"unpipc.h"

struct mq_attr	attr;	/* mq_maxmsg and mq_msgsize both init to 0 */

int
main(int argc, char **argv)
{
	int		c, flags;
	mqd_t	mqd;

	flags = O_RDWR | O_CREAT;
	while ( (c = Getopt(argc, argv, "em:z:")) != -1) {
		switch (c) {
		case 'e':
			flags |= O_EXCL;
			break;

		case 'm':
			attr.mq_maxmsg = atol(optarg);
			break;

		case 'z':
			attr.mq_msgsize = atol(optarg);
			break;
		}
	}
	if (optind != argc - 1)
		err_quit("usage: mqcreate [ -e ] [ -m maxmsg -z msgsize ] <name>");

	if ((attr.mq_maxmsg != 0 && attr.mq_msgsize == 0) ||
		(attr.mq_maxmsg == 0 && attr.mq_msgsize != 0))
		err_quit("must specify both -m maxmsg and -z msgsize");

	printf("about to sleep for 30 seconds before mq_open\n");
	sleep(30);

	mqd = Mq_open(argv[optind], flags, FILE_MODE,
				  (attr.mq_maxmsg != 0) ? &attr : NULL);

	printf("mq_open OK, about to sleep for 30 more seconds\n");
	sleep(30);

	Mq_close(mqd);
	exit(0);
}
