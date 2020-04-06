#include	"unpipc.h"
#include	"square.h"

int
main(int argc, char **argv)
{
	CLIENT		*cl;
	square_in	in;
	square_out	*outp;

	if (argc != 4)
		err_quit("usage: client <hostname> <integer-value> <protocol>");

	cl = Clnt_create(argv[1], SQUARE_PROG, SQUARE_VERS, argv[3]);

	in.arg1 = atol(argv[2]);
	if ( (outp = squareproc_1(&in, cl)) == NULL)
		err_quit("%s", clnt_sperror(cl, argv[1]));

	printf("result: %ld\n", outp->res1);
	exit(0);
}
