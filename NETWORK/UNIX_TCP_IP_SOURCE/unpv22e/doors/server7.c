/* include servproc */
#include	"unpipc.h"
#include	<math.h>
#include	"squareproc.h"
#include	"sqrtproc.h"

void
squareproc(void *cookie, char *dataptr, size_t datasize,
		   door_desc_t *descptr, size_t ndesc)
{
	squareproc_in_t	in;
	squareproc_out_t	out;
	
	memcpy(&in, dataptr, min(sizeof(in), datasize));
	printf("squareproc: thread id %ld, arg = %ld\n",
		   pr_thread_id(NULL), in.arg1);
	sleep(5);

	out.res1 = in.arg1 * in.arg1;
	Door_return((char *) &out, sizeof(out), NULL, 0);
}

void
sqrtproc(void *cookie, char *dataptr, size_t datasize,
		 door_desc_t *descptr, size_t ndesc)
{
	sqrtproc_in_t	in;
	sqrtproc_out_t	out;
	
	memcpy(&in, dataptr, min(sizeof(in), datasize));
	printf("sqrtproc: thread id %ld, arg = %ld\n",
		   pr_thread_id(NULL), in.arg1);
	sleep(5);

	out.res1 = sqrt((double) in.arg1);
	Door_return((char *) &out, sizeof(out), NULL, 0);
}
/* end servproc */

/* include main */
int
main(int argc, char **argv)
{
	int	fd;

	if (argc != 1)
		err_quit("usage: server7");

	fd = Door_create(squareproc, NULL, 0);
	unlink(PATH_SQUARE_DOOR);
	Close(Open(PATH_SQUARE_DOOR, O_CREAT | O_RDWR, FILE_MODE));
	Fattach(fd, PATH_SQUARE_DOOR);

	fd = Door_create(sqrtproc, NULL, 0);
	unlink(PATH_SQRT_DOOR);
	Close(Open(PATH_SQRT_DOOR, O_CREAT | O_RDWR, FILE_MODE));
	Fattach(fd, PATH_SQRT_DOOR);

	for ( ; ; )
		pause();
}
/* end main */
