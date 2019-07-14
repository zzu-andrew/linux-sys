#include	"unpipc.h"
#include	"opt2.h"

int
main(int argc, char **argv)
{
	int		i;
	XDR		xhandle;
	char	*buff;
	long	*lptr;
	args	out;
	size_t	size;

	out.list = NULL;

	buff = Malloc(BUFFSIZE);	/* must be aligned on 4-byte boundary */
	xdrmem_create(&xhandle, buff, BUFFSIZE, XDR_ENCODE);

	if (xdr_args(&xhandle, &out) != TRUE)
		err_quit("xdr_args error");
	size = xdr_getpos(&xhandle);

	lptr = (long *) buff;
	for (i = 0; i < size; i += 4)
		printf("%8lx\n", (long) ntohl(*lptr++));

	exit(0);
}
