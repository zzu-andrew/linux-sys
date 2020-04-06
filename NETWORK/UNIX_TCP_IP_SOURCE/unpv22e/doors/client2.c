#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd;
	long	ival, oval;
	door_arg_t	arg;

	if (argc != 3)
		err_quit("usage: client2 <server-pathname> <integer-value>");

	fd = Open(argv[1], O_RDWR);		/* open the door */

		/* 4set up the arguments and pointer to result */
	ival = atol(argv[2]);
	arg.data_ptr = (char *) &ival;	/* data arguments */
	arg.data_size = sizeof(long);	/* size of data arguments */
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *) &oval;		/* data results */
	arg.rsize = sizeof(long);		/* size of data results */

		/* 4call server procedure and print result */
	Door_call(fd, &arg);
	printf("&oval = %p, data_ptr = %p, rbuf = %p, rsize  = %d\n",
		   &oval, arg.data_ptr, arg.rbuf, arg.rsize);
	printf("result: %ld\n", *((long *) arg.data_ptr));

	exit(0);
}
