/* include px_ipc_name */
#include	"unpipc.h"

char *
px_ipc_name(const char *name)
{
	char	*dir, *dst, *slash;

	if ( (dst = malloc(PATH_MAX)) == NULL)
		return(NULL);

		/* 4can override default directory with environment variable */
	if ( (dir = getenv("PX_IPC_NAME")) == NULL) {
#ifdef	POSIX_IPC_PREFIX
		dir = POSIX_IPC_PREFIX;		/* from "config.h" */
#else
		dir = "/tmp/";				/* default */
#endif
	}
		/* 4dir must end in a slash */
	slash = (dir[strlen(dir) - 1] == '/') ? "" : "/";
	snprintf(dst, PATH_MAX, "%s%s%s", dir, slash, name);

	return(dst);			/* caller can free() this pointer */
}
/* end px_ipc_name */

char *
Px_ipc_name(const char *name)
{
	char	*ptr;

	if ( (ptr = px_ipc_name(name)) == NULL)
		err_sys("px_ipc_name error for %s", name);
	return(ptr);
}
