#include	"unpipc.h"
#include	"data.h"

int
main(int argc, char **argv)
{
	XDR		xhandle;
	data	out;			/* the structure whose values we store */
	char	*buff;			/* the result of the XDR encoding */
	char	vop[2];
	long	vlong[3];
	u_int	size;

	out.short_arg = 1;
	out.long_arg = 2;
	out.vstring_arg = "hello, world";	/* pointer assignment */

	out.fopaque_arg[0] = 99;		/* fixed-length opaque */
	out.fopaque_arg[1] = 88;
	out.fopaque_arg[2] = 77;

	vop[0] = 33;					/* variable-length opaque */
	vop[1] = 44;
	out.vopaque_arg.vopaque_arg_len = 2;
	out.vopaque_arg.vopaque_arg_val = vop;

	out.fshort_arg[0] = 9999;		/* fixed-length array */
	out.fshort_arg[1] = 8888;
	out.fshort_arg[2] = 7777;
	out.fshort_arg[3] = 6666;

	vlong[0] = 123456;				/* variable-length array */
	vlong[1] = 234567;
	vlong[2] = 345678;
	out.vlong_arg.vlong_arg_len = 3;
	out.vlong_arg.vlong_arg_val = vlong;

	out.uarg.result = RESULT_INT;	/* discriminated union */
	out.uarg.union_arg_u.intval = 123;

	buff = Malloc(BUFFSIZE);	/* must be aligned on 4-byte boundary */
	xdrmem_create(&xhandle, buff, BUFFSIZE, XDR_ENCODE);

	if (xdr_data(&xhandle, &out) != TRUE)
		err_quit("xdr_data error");
	size = xdr_getpos(&xhandle);
	Write(STDOUT_FILENO, buff, size);

	exit(0);
}
