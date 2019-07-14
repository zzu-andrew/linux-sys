/* include servproc */
#include	"unpipc.h"
#include	"square.h"

bool_t
squareproc_2_svc(square_in *inp, square_out *outp, struct svc_req *rqstp)
{
	printf("thread %ld started, arg = %ld, auth = %d\n",
		   pr_thread_id(NULL), inp->arg1, rqstp->rq_cred.oa_flavor);
	if (rqstp->rq_cred.oa_flavor == AUTH_SYS) {
		struct authsys_parms	*au;

		au = (struct authsys_parms *)rqstp->rq_clntcred;
		printf("AUTH_SYS: host %s, uid %ld, gid %ld\n",
			   au->aup_machname, (long) au->aup_uid, (long) au->aup_gid);
	}

	sleep(5);
	outp->res1 = inp->arg1 * inp->arg1;
	printf("thread %ld done\n", pr_thread_id(NULL));
	return(TRUE);
}
/* end servproc */

int
square_prog_2_freeresult(SVCXPRT *transp, xdrproc_t xdr_result,
						 caddr_t result)
{
	xdr_free(xdr_result, result);
	return(1);
}
