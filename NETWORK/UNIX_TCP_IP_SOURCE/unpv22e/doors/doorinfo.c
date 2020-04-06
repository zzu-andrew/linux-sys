#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd;
	struct stat	stat;
	struct door_info	info;

	if (argc != 2)
		err_quit("usage: doorinfo <pathname>");

	fd = Open(argv[1], O_RDONLY);
	Fstat(fd, &stat);
	if (S_ISDOOR(stat.st_mode) == 0)
		err_quit("pathname is not a door");

	Door_info(fd, &info);
	printf("server PID = %ld, uniquifier = %ld",
		   (long) info.di_target, (long) info.di_uniquifier);
	if (info.di_attributes & DOOR_LOCAL)
		printf(", DOOR_LOCAL");
	if (info.di_attributes & DOOR_PRIVATE)
		printf(", DOOR_PRIVATE");
	if (info.di_attributes & DOOR_REVOKED)
		printf(", DOOR_REVOKED");
	if (info.di_attributes & DOOR_UNREF)
		printf(", DOOR_UNREF");
	printf("\n");

	exit(0);
}
