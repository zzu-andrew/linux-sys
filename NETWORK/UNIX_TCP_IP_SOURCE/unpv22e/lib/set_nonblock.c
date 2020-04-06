#include	"unpipc.h"

int
set_nonblock(int fd)
{
	int		flags;

    if ( (flags = fcntl(fd, F_GETFL, 0)) < 0)
		return(-1);
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
		return(-1);
	return(0);
}

void
Set_nonblock(int fd)
{
	if (set_nonblock(fd) < 0)
		err_sys("set_nonblock error");
}
