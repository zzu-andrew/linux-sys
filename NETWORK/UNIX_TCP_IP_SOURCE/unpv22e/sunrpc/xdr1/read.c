#include	"unpipc.h"
#include	"data.h"

int
main(int argc, char **argv)
{
	XDR		xhandle;
	int		i;
	char	*buff;
	data	in;
	ssize_t	n;

	buff = Malloc(BUFFSIZE);	/* must be aligned on 4-byte boundary */
	n = Read(STDIN_FILENO, buff, BUFFSIZE);
	printf("read %ld bytes\n", (long) n);

	xdrmem_create(&xhandle, buff, n, XDR_DECODE);
	memset(&in, 0, sizeof(in));
	if (xdr_data(&xhandle, &in) != TRUE)
		err_quit("xdr_data error");

	printf("short_arg = %d, long_arg = %ld, vstring_arg = '%s'\n",
		   in.short_arg, in.long_arg, in.vstring_arg);

	printf("fopaque[] = %d, %d, %d\n",
		   in.fopaque_arg[0], in.fopaque_arg[1], in.fopaque_arg[2]);

	printf("vopaque<> =");
	for (i = 0; i < in.vopaque_arg.vopaque_arg_len; i++)
		printf(" %d", in.vopaque_arg.vopaque_arg_val[i]);
	printf("\n");

	printf("fshort_arg[] = %d, %d, %d, %d\n", in.fshort_arg[0],
		   in.fshort_arg[1], in.fshort_arg[2], in.fshort_arg[3]);

	printf("vlong<> =");
	for (i = 0; i < in.vlong_arg.vlong_arg_len; i++)
		printf(" %ld", in.vlong_arg.vlong_arg_val[i]);
	printf("\n");

	switch (in.uarg.result) {
	case RESULT_INT:
		printf("uarg (int) = %d\n", in.uarg.union_arg_u.intval);
		break;
	case RESULT_DOUBLE:
		printf("uarg (double) = %g\n", in.uarg.union_arg_u.doubleval);
		break;
	default:
		printf("uarg (void)\n");
		break;
	}

	xdr_free(xdr_data, (char *) &in);

	exit(0);
}
