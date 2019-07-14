#include	"unpipc.h"
#include	"squareproc.h"
#include	"sqrtproc.h"

int
main(int argc, char **argv)
{
	int		fdsquare, fdsqrt;
	door_arg_t	arg;
	squareproc_in_t	square_in;
	squareproc_out_t	square_out;
	sqrtproc_in_t	sqrt_in;
	sqrtproc_out_t	sqrt_out;

	if (argc != 2)
		err_quit("usage: client7 <integer-value>");

	fdsquare = Open(PATH_SQUARE_DOOR, O_RDWR);
	fdsqrt = Open(PATH_SQRT_DOOR, O_RDWR);

		/* 4set up the arguments and call squareproc() */
	square_in.arg1 = atol(argv[1]);
	arg.data_ptr = (char *) &square_in;
	arg.data_size = sizeof(square_in);
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *) &square_out;
	arg.rsize = sizeof(square_out);
	Door_call(fdsquare, &arg);

		/* 4set up the arguments and call sqrtproc() */
	sqrt_in.arg1 = atol(argv[1]);
	arg.data_ptr = (char *) &sqrt_in;
	arg.data_size = sizeof(sqrt_in);
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *) &sqrt_out;
	arg.rsize = sizeof(sqrt_out);
	Door_call(fdsqrt, &arg);

	printf("result: %ld %g\n", square_out.res1, sqrt_out.res1);

	exit(0);
}
