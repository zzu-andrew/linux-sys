#include	"unpipc.h"
#include	"opt1.h"

int
main(int argc, char **argv)
{
	int		i;
	XDR		xhandle;
	char	*buff;
	long	lval2, lval3, *lptr;
	args	out;
	size_t	size;

	out.arg1.flag = TRUE;
	out.arg1.optlong_u.val = 5;

	lval2 = 9876;
	out.arg2.arg2_len = 1;
	out.arg2.arg2_val = &lval2;

	lval3 = 123;
	out.arg3 = &lval3;

	buff = Malloc(BUFFSIZE);	/* must be aligned on 4-byte boundary */
	xdrmem_create(&xhandle, buff, BUFFSIZE, XDR_ENCODE);

	if (xdr_args(&xhandle, &out) != TRUE)
		err_quit("xdr_args error");
	size = xdr_getpos(&xhandle);

	lptr = (long *) buff;
	for (i = 0; i < size; i += 4)
		printf("%ld\n", (long) ntohl(*lptr++));

	exit(0);
}
