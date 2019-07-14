#include	"unpipc.h"

int
main(int argc, char **argv)
{
	int		door, fd;
	char	argbuf[BUFFSIZE], resbuf[BUFFSIZE], buff[BUFFSIZE];
	size_t	len, n;
	door_arg_t	arg;

	if (argc != 2)
		err_quit("usage: clientfd1 <server-pathname>");

	door = Open(argv[1], O_RDWR);		/* open the door */

	Fgets(argbuf, BUFFSIZE, stdin);		/* read pathname of file to open */
	len = strlen(argbuf);
	if (argbuf[len-1] == '\n')
		len--;				/* delete newline from fgets() */

		/* 4set up the arguments and pointer to result */
	arg.data_ptr = argbuf;		/* data argument */
	arg.data_size = len + 1;	/* size of data argument */
	arg.desc_ptr = NULL;
	arg.desc_num = 0;
	arg.rbuf = resbuf;			/* data results */
	arg.rsize = BUFFSIZE;		/* size of data results */

	Door_call(door, &arg);		/* call server procedure */

	if (arg.data_size != 0)
		err_quit("%.*s", arg.data_size, arg.data_ptr);
	else if (arg.desc_ptr == NULL)
		err_quit("desc_ptr is NULL");
	else if (arg.desc_num != 1)
		err_quit("desc_num = %d", arg.desc_num);
	else if (arg.desc_ptr->d_attributes != DOOR_DESCRIPTOR)
		err_quit("d_attributes = %d", arg.desc_ptr->d_attributes);

	fd = arg.desc_ptr->d_data.d_desc.d_descriptor;
	while ( (n = Read(fd, buff, BUFFSIZE)) > 0)
		Write(STDOUT_FILENO, buff, n);

	exit(0);
}
