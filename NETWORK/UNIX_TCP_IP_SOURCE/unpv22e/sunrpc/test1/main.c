#include	"unpipc.h"
#include	"data.h"

int
main(int argc, char **argv)
{
	XDR		xhandle;
	char	*buff;

	/* if (argc != 2)
		err_quit("usage: udpcli <IPaddress>"); */

	buff = Malloc(BUFFSIZE);	/* must be aligned on 4-byte boundary */
	xdrmem_create(&xhandle, buff, BUFFSIZE, XDR_ENCODE);

	exit(0);
}
