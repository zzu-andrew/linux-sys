#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd[2];
	char	buff[7];
	struct stat	info;

	if (argc != 2)
		err_quit("usage: test1 <pathname>");

	Mkfifo(argv[1], FILE_MODE);
	fd[0] = Open(argv[1], O_RDONLY | O_NONBLOCK);
	fd[1] = Open(argv[1], O_WRONLY | O_NONBLOCK);

		/* 4check sizes when FIFO is empty */
	Fstat(fd[0], &info);
	printf("fd[0]: st_size = %ld\n", (long) info.st_size);
	Fstat(fd[1], &info);
	printf("fd[1]: st_size = %ld\n", (long) info.st_size);

	Write(fd[1], buff, sizeof(buff));

		/* 4check sizes when FIFO contains 7 bytes */
	Fstat(fd[0], &info);
	printf("fd[0]: st_size = %ld\n", (long) info.st_size);
	Fstat(fd[1], &info);
	printf("fd[1]: st_size = %ld\n", (long) info.st_size);

	exit(0);
}
