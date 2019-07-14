#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		i, fd;
	struct stat	stat;
	unsigned char	c, *ptr;

	if (argc != 2)
		err_quit("usage: shmread <name>");

		/* 4open, get size, map */
	fd = Shm_open(argv[1], O_RDONLY, FILE_MODE);
	Fstat(fd, &stat);
	ptr = Mmap(NULL, stat.st_size, PROT_READ,
			   MAP_SHARED, fd, 0);
	Close(fd);

		/* 4check that ptr[0] = 0, ptr[1] = 1, etc. */
	for (i = 0; i < stat.st_size; i++)
		if ( (c = *ptr++) != (i % 256))
			err_ret("ptr[%d] = %d", i, c);

	exit(0);
}
