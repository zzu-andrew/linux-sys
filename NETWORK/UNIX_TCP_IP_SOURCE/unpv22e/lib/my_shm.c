/* include my_shm */
#include	"unpipc.h"

void *
my_shm(size_t nbytes)
{
	void	*shared;

#if		defined(MAP_ANON)
	shared = mmap(NULL, nbytes, PROT_READ | PROT_WRITE,
				  MAP_ANON | MAP_SHARED, -1, 0);

#elif	defined(HAVE_DEV_ZERO)
	int		fd;

		/* 4memory map /dev/zero */
	if ( (fd = open("/dev/zero", O_RDWR)) == -1)
		return(MAP_FAILED);
	shared = mmap(NULL, nbytes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	close(fd);

# else
# error cannot determine what type of anonymous shared memory to use
# endif
	return(shared);		/* MAP_FAILED on error */
}
/* end my_shm */

void *
My_shm(size_t nbytes)
{
	void	*shared;

	if ( (shared = my_shm(nbytes)) == MAP_FAILED)
		err_sys("my_shm error");
	return(shared);
}
