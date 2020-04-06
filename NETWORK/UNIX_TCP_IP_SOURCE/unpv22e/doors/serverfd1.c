/* include servproc */
#include	"unpipc.h"

void
servproc(void *cookie, char *dataptr, size_t datasize,
		 door_desc_t *descptr, size_t ndesc)
{
	int		fd;
	char	resbuf[BUFFSIZE];
	door_desc_t	desc;

	dataptr[datasize-1] = 0;		/* null terminate */
	if ( (fd = open(dataptr, O_RDONLY)) == -1) {
			/* 4error: must tell client */
		snprintf(resbuf, BUFFSIZE, "%s: can't open, %s",
				 dataptr, strerror(errno));
		Door_return(resbuf, strlen(resbuf), NULL, 0);

	} else {
			/* 4open succeeded: return descriptor */
		desc.d_data.d_desc.d_descriptor = fd;
		desc.d_attributes = DOOR_DESCRIPTOR;
		Door_return(NULL, 0, &desc, 1);
	}
}
/* end servproc */

int
main(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		err_quit("usage: serverfd1 <server-pathname>");

		/* 4create a door descriptor and attach to pathname */
	fd = Door_create(servproc, NULL, 0);

	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_RDWR, FILE_MODE));
	Fattach(fd, argv[1]);

		/* 4servproc() handles all client requests */
	for ( ; ; )
		pause();
}
