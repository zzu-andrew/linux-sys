/* include bw_door1 */
#include	"unpipc.h"

void	reader(int, int);
void	writer(int);
void	server(void *, char *, size_t, door_desc_t *, size_t);

void	*buf;
int		totalnbytes, xfersize, contpipe[2];

int
main(int argc, char **argv)
{
	int		i, nloop, doorfd;
	char	c;
	pid_t	childpid;
	ssize_t	n;

	if (argc != 5)
		err_quit("usage: bw_door <pathname> <#loops> <#mbytes> <#bytes/write>");
	nloop = atoi(argv[2]);
	totalnbytes = atoi(argv[3]) * 1024 * 1024;
	xfersize = atoi(argv[4]);

	buf = Valloc(xfersize);
	Touch(buf, xfersize);

	unlink(argv[1]);
	Close(Open(argv[1], O_CREAT | O_EXCL | O_RDWR, FILE_MODE));
	Pipe(contpipe);		/* assumes full-duplex SVR4 pipe */

	if ( (childpid = Fork()) == 0) {
			/* 4child = client = writer */
		if ( (n = Read(contpipe[0], &c, 1)) != 1)
			err_quit("child: pipe read returned %d", n);
		doorfd = Open(argv[1], O_RDWR);

		writer(doorfd);
		exit(0);
	}
		/* 4parent = server = reader */
	doorfd = Door_create(server, NULL, 0);
	Fattach(doorfd, argv[1]);
	Write(contpipe[1], &c, 1);	/* tell child door is ready */

	Start_time();
	for (i = 0; i < nloop; i++)
		reader(doorfd, totalnbytes);
	printf("bandwidth: %.3f MB/sec\n",
		   totalnbytes / Stop_time() * nloop);
	kill(childpid, SIGTERM);
	unlink(argv[1]);
	exit(0);
}
/* end bw_door1 */

/* include bw_door2 */
void
writer(int doorfd)
{
	int		ntowrite;
	door_arg_t	arg;

	arg.desc_ptr = NULL;	/* no descriptors to pass */
	arg.desc_num = 0;
	arg.rbuf = NULL;		/* no return values expected */
	arg.rsize = 0;

	for ( ; ; ) {
		Read(contpipe[0], &ntowrite, sizeof(ntowrite));

		while (ntowrite > 0) {
			arg.data_ptr = buf;
			arg.data_size = xfersize;
			Door_call(doorfd, &arg);
			ntowrite -= xfersize;
		}
	}
}

static int	ntoread, nread;

void
server(void *cookie, char *argp, size_t arg_size,
       door_desc_t *dp, size_t n_descriptors)
{
	char	c;

	nread += arg_size;
	if (nread >= ntoread)
		Write(contpipe[0], &c, 1);	/* tell reader() we are all done */

    Door_return(NULL, 0, NULL, 0);
}

void
reader(int doorfd, int nbytes)
{
	char	c;
	ssize_t	n;

	ntoread = nbytes;	/* globals for server() procedure */
	nread = 0;

	Write(contpipe[1], &nbytes, sizeof(nbytes));

	if ( (n = Read(contpipe[1], &c, 1)) != 1)
		err_quit("reader: pipe read returned %d", n);
}
/* end bw_door2 */
