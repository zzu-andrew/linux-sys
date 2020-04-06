/* include sem_open1 */
#include	"unpipc.h"
#include	"semaphore.h"

#include	<stdarg.h>		/* for variable arg lists */
#define		MAX_TRIES	10	/* for waiting for initialization */

mysem_t	*
mysem_open(const char *pathname, int oflag, ... )
{
	int		i, fd, semflag, semid, save_errno;
	key_t	key;
	mode_t	mode;
	va_list	ap;
	mysem_t	*sem;
	union semun	arg;
	unsigned int	value;
	struct semid_ds	seminfo;
	struct sembuf	initop;

		/* 4no mode for sem_open() w/out O_CREAT; guess */
	semflag = SVSEM_MODE;
	semid = -1;

	if (oflag & O_CREAT) {
		va_start(ap, oflag);		/* init ap to final named argument */
		mode = va_arg(ap, va_mode_t);
		value = va_arg(ap, unsigned int);
		va_end(ap);

			/* 4convert to key that will identify System V semaphore */
		if ( (fd = open(pathname, oflag, mode)) == -1)
			return(SEM_FAILED);
		close(fd);
		if ( (key = ftok(pathname, 0)) == (key_t) -1)
			return(SEM_FAILED);

		semflag = IPC_CREAT | (mode & 0777);
		if (oflag & O_EXCL)
			semflag |= IPC_EXCL;

			/* 4create the System V semaphore with IPC_EXCL */
		if ( (semid = semget(key, 1, semflag | IPC_EXCL)) >= 0) {
				/* 4success, we're the first so initialize to 0 */
			arg.val = 0;
			if (semctl(semid, 0, SETVAL, arg) == -1)
				goto err;
				/* 4then increment by value to set sem_otime nonzero */
			if (value > SEMVMX) {
				errno = EINVAL;
				goto err;
			}
        	initop.sem_num = 0;
        	initop.sem_op  = value;
        	initop.sem_flg = 0;
			if (semop(semid, &initop, 1) == -1)
				goto err;
			goto finish;

		} else if (errno != EEXIST || (semflag & IPC_EXCL) != 0)
			goto err;
		/* else fall through */
	}
/* end sem_open1 */
/* include sem_open2 */
	/*
	 * (O_CREAT not secified) or
	 * (O_CREAT without O_EXCL and semaphore already exists).
	 * Must open semaphore and make certain it has been initialized.
	 */
	if ( (key = ftok(pathname, 0)) == (key_t) -1)
		goto err;
	if ( (semid = semget(key, 0, semflag)) == -1)
		goto err;

	arg.buf = &seminfo;
	for (i = 0; i < MAX_TRIES; i++) {
		if (semctl(semid, 0, IPC_STAT, arg) == -1)
			goto err;
		if (arg.buf->sem_otime != 0)
			goto finish;
		sleep(1);
	}
	errno = ETIMEDOUT;
err:
	save_errno = errno;		/* don't let semctl() change errno */
	if (semid != -1)
		semctl(semid, 0, IPC_RMID);
	errno = save_errno;
	return(SEM_FAILED);

finish:
/* *INDENT-OFF* */
	if ( (sem = malloc(sizeof(mysem_t))) == NULL)
		goto err;
/* *INDENT-ON* */
	sem->sem_semid = semid;
	sem->sem_magic = SEM_MAGIC;
	return(sem);
}
/* end sem_open2 */

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
