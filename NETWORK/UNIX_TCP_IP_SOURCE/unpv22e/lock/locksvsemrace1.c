#include	"unpipc.h"

#define	LOCK_PATH	"/tmp/svsemlock"
#define	MAX_TRIES	10

int		semid, initflag, pipefd[2];
struct sembuf	postop, waitop;

void
my_lock(int fd)
{
	int		oflag, i;
	union semun	arg;
	struct semid_ds	seminfo;

	if (initflag == 0) {
		oflag = IPC_CREAT | IPC_EXCL | SVSEM_MODE;
		if ( (semid = semget(Ftok(LOCK_PATH, 0), 1, oflag)) >= 0) {
				/* 4success, we're the first so initialize */
			arg.val = 1;
			Semctl(semid, 0, SETVAL, arg);

		} else if (errno == EEXIST) {
				/* 4someone else has created; make sure it's initialized */
			semid = Semget(Ftok(LOCK_PATH, 0), 1, SVSEM_MODE);
			arg.buf = &seminfo;
			for (i = 0; i < MAX_TRIES; i++) {
				Semctl(semid, 0, IPC_STAT, arg);
				if (arg.buf->sem_otime != 0)
					goto init;
				Write(pipefd[1], "", 1);	/* tell parent */
				sleep(1);
			}
			err_quit("semget OK, but semaphore not initialized");

		} else
			err_sys("semget error");
init:
		initflag = 1;
		postop.sem_num = 0;		/* and init the two semop() structures */
		postop.sem_op  = 1;
		postop.sem_flg = SEM_UNDO;
		waitop.sem_num = 0;
		waitop.sem_op  = -1;
		waitop.sem_flg = SEM_UNDO;
	}
	Semop(semid, &waitop, 1);		/* down by 1 */
}

void
my_unlock(int fd)
{
	Semop(semid, &postop, 1);		/* up by 1 */
}

#define	SEQFILE	"seqno"		/* filename */

int
main(int argc, char **argv)
{
	int		fd = 0, stat, nconflicts;
	long	i, j, nproc;
	sem_t	*ptr;
	pid_t	pid;
	ssize_t	n;

	if (argc != 2)
		err_quit("usage: locksvsemrace1 <#processes>");
	nproc = atol(argv[1]);
	Pipe(pipefd);

	ptr = My_shm(sizeof(sem_t));	/* create memory-based semaphore */
	Sem_init(ptr, 1, 0);

	for (j = 0; j < nproc; j++) {
		if (Fork() == 0) {
				/* 4child */
			Sem_wait(ptr);		/* wait for parent to start children */
			for (i = 0; i < 10; i++) {
				my_lock(fd);		/* lock the file */
				my_unlock(fd);		/* unlock the file */
			}
			exit(0);
		}
		/* parent loops around, creating next child */
	}
	for (j = 0; j < nproc; j++)
		Sem_post(ptr);	/* start all the children */

	/* now just wait for all the children to finish */
	while ( (pid = waitpid(-1, &stat, WNOHANG)) > 0)
		;
	Close(pipefd[1]);
	nconflicts = 0;
	while ( (n = Read(pipefd[0], &stat, 1)) > 0)
		nconflicts += n;
	printf("%d conflicts\n", nconflicts);
	exit(0);
}
