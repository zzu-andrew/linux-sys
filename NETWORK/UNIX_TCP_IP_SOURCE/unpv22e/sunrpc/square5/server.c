#include	"unpipc.h"
#include	"square.h"

square_out *
squareproc_1_svc(square_in *inp, struct svc_req *rqstp)
{
	static square_out	out;

	printf("thread %ld started, arg = %ld\n",
		   pr_thread_id(NULL), inp->arg1);
	sleep(10000);
	out.res1 = inp->arg1 * inp->arg1;
	printf("thread %ld done\n", pr_thread_id(NULL));

	return(&out);
}
