#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd, n;
	char	buff[BUFFSIZE];

	if (argc != 2)
		err_quit("usage: mycat1 <pathname>");

	fd = Open(argv[1], O_RDONLY);

	while ( (n = Read(fd, buff, BUFFSIZE)) > 0)
		Write(STDOUT_FILENO, buff, n);

	exit(0);
}
