#include	"unpipc.h"

struct shmstruct {	/* struct stored in shared memory */
  int	count;
};
sem_t	*mutex;		/* pointer to named semaphore */

int
main(int argc, char **argv)
{
	int		fd;
	struct shmstruct	*ptr;

	if (argc != 3)
		err_quit("usage: server1 <shmname> <semname>");

	shm_unlink(Px_ipc_name(argv[1]));		/* OK if this fails */
		/* 4create shm, set its size, map it, close descriptor */
	fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_EXCL, FILE_MODE);
	Ftruncate(fd, sizeof(struct shmstruct));
	ptr = Mmap(NULL, sizeof(struct shmstruct), PROT_READ | PROT_WRITE,
			   MAP_SHARED, fd, 0);
	Close(fd);

	sem_unlink(Px_ipc_name(argv[2]));		/* OK if this fails */
	mutex = Sem_open(Px_ipc_name(argv[2]), O_CREAT | O_EXCL, FILE_MODE, 1);
	Sem_close(mutex);

	exit(0);
}
