#include	"unpipc.h"
#include	"square.h"

square_out *
squareproc_1_svc(square_in *inp, struct svc_req *rqstp)
{
	static square_out	out;

	printf("server procedure started\n");
	out.res1 = inp->arg1 * inp->arg1;
	abort();
	return(&out);
}
