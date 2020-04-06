/* include lat_door1 */
#include	"unpipc.h"

void
server(void *cookie, char *argp, size_t arg_size,
       door_desc_t *dp, size_t n_descriptors)
{
	char	c;

	Door_return(&c, sizeof(char), NULL, 0);
}

int
main(int argc, char **argv)
{
	int		i, nloop, doorfd, contpipe[2];
	char	c;
	pid_t	childpid;
	door_arg_t	arg;

	if (argc != 3)
		err_quit("usage: lat_door <pathname> <#loops>");
	nloop = atoi(argv[2]);

	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE));
	Pipe(contpipe);

	if ( (childpid = Fork()) == 0) {
		doorfd = Door_create(server, NULL, 0);
		Fattach(doorfd, argv[1]);
		Write(contpipe[1], &c, 1);

		for ( ; ; )		/* child = server */
			pause();
		exit(0);
	}
	arg.data_ptr = &c;	/* parent = client */
	arg.data_size = sizeof(char);
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = &c;
	arg.rsize = sizeof(char);

	if (Read(contpipe[0], &c, 1) != 1)	/* wait for child to create */
		err_quit("pipe read error");
	doorfd = Open(argv[1], O_RDWR);
	Door_call(doorfd, &arg);	/* once to start everything */

	Start_time();
	for (i = 0; i < nloop; i++)
		Door_call(doorfd, &arg);
	printf("latency: %.3f usec\n", Stop_time() / nloop);

	Kill(childpid, SIGTERM);
	unlink(argv[1]);
	exit(0);
}
/* end lat_door1 */
