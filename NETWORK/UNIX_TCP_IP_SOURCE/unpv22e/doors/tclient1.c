#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		fd;
	long	ivals[4], ovals[4];
	door_arg_t	arg;
	struct stat	stat;
	struct door_info	info;

	if (argc != 2)
		err_quit("usage: client1 <pathname>");

	fd = Open(argv[1], O_RDWR);
	Fstat(fd, &stat);
	printf("pid = %ld, fmt = %lx\n",
		   (long) getpid(), (long) stat.st_mode & S_IFMT);

	Door_info(fd, &info);
	printf("di_target = %ld, di_proc = %p, di_data = %p, di_attr = %x\n",
		   (long) info.di_target, (void *) info.di_proc,
		   (void *) info.di_data, info.di_attributes);

	ivals[0] = 1;
	ivals[1] = 3;
	ivals[2] = 6;
	ivals[3] = 9;
	arg.data_ptr = (char *) ivals;
	arg.data_size = 4 * sizeof(long);
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = (char *) ovals;
	arg.rsize = sizeof(ovals);

	Door_call(fd, &arg);

	if (arg.data_ptr != (char *) ovals)
		printf("arg.data_ptr = %p\n", arg.data_ptr);
	printf("result: %ld %ld %ld %ld\n",
		   ovals[0], ovals[1], ovals[2], ovals[3]);

	exit(0);
}
