#include	"unpipc.h"
#include	"square.h"

bool_t
squareproc_2_svc(square_in *inp, square_out *outp, struct svc_req *rqstp)
{
	printf("thread %ld started, arg = %ld\n",
		   pr_thread_id(NULL), inp->arg1);
	outp->res1 = inp->arg1 * inp->arg1;
    pthread_exit(NULL);         /* and see what happens at client */
	return(TRUE);
}

int
square_prog_2_freeresult(SVCXPRT *transp, xdrproc_t xdr_result,
						 caddr_t result)
{
	xdr_free(xdr_result, result);
	return(1);
}
