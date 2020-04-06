#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd, i;
	char	*ptr;
	size_t	filesize, mmapsize, pagesize;

	if (argc != 4)
		err_quit("usage: test1 <pathname> <filesize> <mmapsize>");
	filesize = atoi(argv[2]);
	mmapsize = atoi(argv[3]);

		/* 4open file: create or truncate; set file size */
	fd = Open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE);
	Lseek(fd, filesize-1, SEEK_SET);
	Write(fd, "", 1);

	ptr = Mmap(NULL, mmapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	Close(fd);

	pagesize = Sysconf(_SC_PAGESIZE);
	printf("PAGESIZE = %ld\n", (long) pagesize);

	for (i = 0; i < max(filesize, mmapsize); i += pagesize) {
		printf("ptr[%d] = %d\n", i, ptr[i]);
		ptr[i] = 1;
		printf("ptr[%d] = %d\n", i + pagesize - 1, ptr[i + pagesize - 1]);
		ptr[i + pagesize - 1] = 1;
	}
	printf("ptr[%d] = %d\n", i, ptr[i]);
	
	exit(0);
}
