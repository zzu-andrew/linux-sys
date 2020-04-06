/* Verify that two readers can lock the same region */
#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd;

	fd = Open("test1.data", O_RDWR | O_CREAT, (mode_t) FILE_MODE);

	Read_lock(fd, 0, SEEK_SET, 0);		/* parent read locks entire file */
	printf("%s: parent has read lock\n", Gf_time());

	if (Fork() == 0) {
			/* 4child */
		Read_lock(fd, 0, SEEK_SET, 0);	/* this should work */
		printf("%s: child has read lock\n", Gf_time());
		sleep(2);
		Un_lock(fd, 0, SEEK_SET, 0);
		printf("%s: child releases read lock\n", Gf_time());

		Read_lock(fd, 0, SEEK_SET, 0);	/* this should work */
		printf("%s: child has read lock\n", Gf_time());
		sleep(2);
		exit(0);
	}

	/* parent */
	sleep(4);
	Un_lock(fd, 0, SEEK_SET, 0);
	printf("%s: parent releases read lock\n", Gf_time());
	exit(0);
}
