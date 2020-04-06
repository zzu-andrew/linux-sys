#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd, i;
	char	*ptr;
	size_t	shmsize, mmapsize, pagesize;

	if (argc != 4)
		err_quit("usage: test1 <name> <shmsize> <mmapsize>");
	shmsize = atoi(argv[2]);
	mmapsize = atoi(argv[3]);

		/* open shm: create or truncate; set shm size */
	fd = Shm_open(Px_ipc_name(argv[1]), O_RDWR | O_CREAT | O_TRUNC,
				  FILE_MODE);
	Ftruncate(fd, shmsize);
/* $$.bp$$ */
	ptr = Mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	pagesize = Sysconf(_SC_PAGESIZE);
	printf("PAGESIZE = %ld\n", (long) pagesize);

	for (i = 0; i < max(shmsize, mmapsize); i += pagesize) {
		printf("ptr[%d] = %d\n", i, ptr[i]);
		ptr[i] = 1;
		printf("ptr[%d] = %d\n", i + pagesize - 1, ptr[i + pagesize - 1]);
		ptr[i + pagesize - 1] = 1;
	}
	printf("ptr[%d] = %d\n", i, ptr[i]);
	
	exit(0);
}
