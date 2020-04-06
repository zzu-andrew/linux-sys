#include	"unpipc.h"
#include	"bw_sunrpc.h"

void	*buf;
int		totalnbytes, xfersize;

int
main(int argc, char **argv)
{
	int		i, nloop, ntowrite;
	CLIENT	*cl;
	data_in	in;

	if (argc != 6)
		err_quit("usage: bw_sunrpc_client <hostname> <#loops>"
				 " <#mbytes> <#bytes/write> <protocol>");
	nloop = atoi(argv[2]);
	totalnbytes = atoi(argv[3]) * 1024 * 1024;
	xfersize = atoi(argv[4]);

	buf = Valloc(xfersize);
	Touch(buf, xfersize);

	cl = Clnt_create(argv[1], BW_SUNRPC_PROG, BW_SUNRPC_VERS, argv[5]);

	Start_time();
	for (i = 0; i < nloop; i++) {
		ntowrite = totalnbytes;
		while (ntowrite > 0) {
			in.data.data_len = xfersize;
			in.data.data_val = buf;
			if (bw_sunrpc_1(&in, cl) == NULL)
				err_quit("%s", clnt_sperror(cl, argv[1]));
			ntowrite -= xfersize;
		}
	}
	printf("bandwidth: %.3f MB/sec\n",
		   totalnbytes / Stop_time() * nloop);
	exit(0);
}
