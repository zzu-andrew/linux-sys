#include	"unpipc.h"
#include	"lat_sunrpc.h"

int
main(int argc, char **argv)
{
	int		i, nloop;
	CLIENT	*cl;
	struct timeval	tv;

	if (argc != 4)
		err_quit("usage: lat_sunrpc_client <hostname> <#loops> <protocol>");
	nloop = atoi(argv[2]);

	cl = Clnt_create(argv[1], BW_SUNRPC_PROG, BW_SUNRPC_VERS, argv[3]);

	tv.tv_sec = 10;
	tv.tv_usec = 0;
	Start_time();
	for (i = 0; i < nloop; i++) {
		if (clnt_call(cl, NULLPROC, xdr_void, NULL,
					  xdr_void, NULL, tv) != RPC_SUCCESS)
			err_quit("%s", clnt_sperror(cl, argv[1]));
	}
	printf("latency: %.3f usec\n", Stop_time() / nloop);
	exit(0);
}
