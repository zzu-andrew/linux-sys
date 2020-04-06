#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		i, fd;
	struct stat	stat;
	unsigned char	*ptr;

	if (argc != 2)
		err_quit("usage: shmwrite <name>");

		/* 4open, get size, map */
	fd = Shm_open(argv[1], O_RDWR, FILE_MODE);
	Fstat(fd, &stat);
	ptr = Mmap(NULL, stat.st_size, PROT_READ | PROT_WRITE,
			   MAP_SHARED, fd, 0);
	Close(fd);

		/* 4set: ptr[0] = 0, ptr[1] = 1, etc. */
	for (i = 0; i < stat.st_size; i++)
		*ptr++ = i % 256;

	exit(0);
}
