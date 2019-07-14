/* include sem_open */
#include	"unpipc.h"
#include	"semaphore.h"

#include	<stdarg.h>		/* for variable arg lists */

mysem_t	*
mysem_open(const char *pathname, int oflag, ... )
{
	int		i, flags, save_errno;
	char	c;
	mode_t	mode;
	va_list	ap;
	mysem_t	*sem;
	unsigned int	value;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		value = va_arg(ap, unsigned int);
		va_end(ap);

		if (mkfifo(pathname, mode) < 0) {
			if (errno == EEXIST && (oflag & O_EXCL) == 0)
				oflag &= ~O_CREAT;	/* already exists, OK */
			else
				return(SEM_FAILED);
		}
	}

/* *INDENT-OFF* */
	if ( (sem = malloc(sizeof(mysem_t))) == NULL)
		return(SEM_FAILED);
	sem->sem_fd[0] = sem->sem_fd[1] = -1;

	if ( (sem->sem_fd[0] = open(pathname, O_RDONLY | O_NONBLOCK)) < 0)
		goto error;
	if ( (sem->sem_fd[1] = open(pathname, O_WRONLY | O_NONBLOCK)) < 0)
		goto error;
/* *INDENT-ON* */

		/* 4turn off nonblocking for sem_fd[0] */
	if ( (flags = fcntl(sem->sem_fd[0], F_GETFL, 0)) < 0)
		goto error;
	flags &= ~O_NONBLOCK;
	if (fcntl(sem->sem_fd[0], F_SETFL, flags) < 0)
		goto error;

	if (oflag & O_CREAT) {		/* initialize semaphore */
		for (i = 0; i < value; i++)
			if (write(sem->sem_fd[1], &c, 1) != 1)
				goto error;
	}

	sem->sem_magic = SEM_MAGIC;
	return(sem);

error:
	save_errno = errno;
	if (oflag & O_CREAT)
		unlink(pathname);		/* if we created FIFO */
	close(sem->sem_fd[0]);		/* ignore error */
	close(sem->sem_fd[1]);		/* ignore error */
	free(sem);
	errno = save_errno;
	return(SEM_FAILED);
}
/* end sem_open */

mysem_t	*
Mysem_open(const char *pathname, int oflag, ... )
{
	va_list	ap;
	mode_t	mode;
	mysem_t	*sem;
	unsigned int	value;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		value = va_arg(ap, unsigned int);
		if ( (sem = mysem_open(pathname, oflag, mode, value)) == SEM_FAILED)
			err_sys("mysem_open error for %s", pathname);
		va_end(ap);
	} else {
		if ( (sem = mysem_open(pathname, oflag)) == SEM_FAILED)
			err_sys("mysem_open error for %s", pathname);
	}

	return(sem);
}
