#include	"unpipc.h"

#define	SEM_NAME	"mysem"

/* include diff */
int
main(int argc, char **argv)
{
	int		fd, i, nloop;
	int		*ptr;
	sem_t	*mutex;

	if (argc != 2)
		err_quit("usage: incr_dev_zero <#loops>");
	nloop = atoi(argv[1]);

		/* 4open /dev/zero, map into memory */
	fd = Open("/dev/zero", O_RDWR);
	ptr = Mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);
/* end diff */

		/* 4create, initialize, and unlink semaphore */
	mutex = Sem_open(Px_ipc_name(SEM_NAME), O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_unlink(Px_ipc_name(SEM_NAME));

	setbuf(stdout, NULL);	/* stdout is unbuffered */
	if (Fork() == 0) {		/* child */
		for (i = 0; i < nloop; i++) {
			Sem_wait(mutex);
			printf("child: %d\n", (*ptr)++);
			Sem_post(mutex);
		}
		exit(0);
	}

		/* 4parent */
	for (i = 0; i < nloop; i++) {
		Sem_wait(mutex);
		printf("parent: %d\n", (*ptr)++);
		Sem_post(mutex);
	}
	exit(0);
}
