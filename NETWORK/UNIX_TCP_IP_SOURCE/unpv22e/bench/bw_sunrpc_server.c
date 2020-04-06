#include	"unpipc.h"
#include	"bw_sunrpc.h"

#ifndef	RPCGEN_ANSIC
#define	bw_sunrpc_1_svc	bw_sunrpc_1
#endif

void *
bw_sunrpc_1_svc(data_in *inp, struct svc_req *rqstp)
{
	static int	nbytes;

	nbytes = inp->data.data_len;
	return(&nbytes);	/* must be nonnull, but xdr_void() will ignore */
}
