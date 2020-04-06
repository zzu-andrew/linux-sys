#include	"unpipc.h"
#include	"opt2.h"

int
main(int argc, char **argv)
{
	int		i;
	XDR		xhandle;
	long	*lptr;
	args	out;				/* the structure that we fill */
	char	*buff;				/* the XDR encoded result */
	mylist	nameval[4];			/* up to 4 list entries */
	size_t	size;

	out.list = &nameval[2];		/* [2] -> [1] -> [0] */
	nameval[2].name = "name1";
	nameval[2].value = 0x1111;
	nameval[2].next = &nameval[1];
	nameval[1].name = "namee2";
	nameval[1].value = 0x2222;
	nameval[1].next = &nameval[0];
	nameval[0].name = "nameee3";
	nameval[0].value = 0x3333;
	nameval[0].next = NULL;

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
