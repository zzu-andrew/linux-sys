#include	"unpipc.h"

CLIENT *
Clnt_create(const char *host, u_long prog, u_long vers, const char *proto)
{
	CLIENT	*cl;

	if ( (cl = clnt_create(host, prog, vers, proto)) == NULL) {
		clnt_pcreateerror(host);
		err_quit("clnt_create error");
	}
	return(cl);
}

void
Clnt_control(CLIENT *cl, u_int req, char *ptr)
{
	if (clnt_control(cl, req, ptr) == FALSE) {
		err_quit("clnt_control error");
	}
}
