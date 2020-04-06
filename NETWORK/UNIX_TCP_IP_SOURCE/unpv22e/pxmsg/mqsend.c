#include	"unpipc.h"

int
main(int argc, char **argv)
{
	mqd_t	mqd;
	void	*ptr;
	size_t	len;
	uint_t	prio;

	if (argc != 4)
		err_quit("usage: mqsend <name> <#bytes> <priority>");
	len = atoi(argv[2]);
	prio = atoi(argv[3]);

	mqd = Mq_open(argv[1], O_WRONLY);

	ptr = Calloc(len, sizeof(char));
	Mq_send(mqd, ptr, len, prio);

	exit(0);
}
