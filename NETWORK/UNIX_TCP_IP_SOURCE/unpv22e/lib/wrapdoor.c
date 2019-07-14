/*
 * doors wrapper functions.
 */

#include	"unpipc.h"

void
Door_bind(int fd)
{
	if (door_bind(fd) == -1)
		err_sys("door_bind error");
}

void
Door_call(int fd, door_arg_t *arg)
{
	if (door_call(fd, arg) == -1)
		err_sys("door_call error");
}

int
Door_create(Door_server_proc *proc, void *cookie, u_int attr)
{
	int		rc;

	if ( (rc = door_create(proc, cookie, attr)) == -1)
		err_sys("door_create error");
	return(rc);
}

void
Door_cred(door_cred_t *info)
{
	if (door_cred(info) == -1)
		err_sys("door_cred error");
}

void
Door_info(int fd, door_info_t *info)
{
	if (door_info(fd, info) == -1)
		err_sys("door_info error");
}

void
Door_return(char *data_ptr, size_t data_size,
			door_desc_t *desc_ptr, size_t num_desc)
{
	if (door_return(data_ptr, data_size, desc_ptr, num_desc) == -1)
		err_sys("door_return error");
}

void
Door_revoke(int fd)
{
	if (door_revoke(fd) == -1)
		err_sys("door_revoke error");
}

Door_create_proc *
Door_server_create(Door_create_proc *new)
{
	Door_create_proc	*old;

	old = door_server_create(new);
	return(old);
}

void
Door_unbind(void)
{
	if (door_unbind() == -1)
		err_sys("door_unbind error");
}
