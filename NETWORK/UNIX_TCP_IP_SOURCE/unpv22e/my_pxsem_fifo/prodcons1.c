/*
 * This program is used to test the semaphore implementation using FIFOs.
 * Note that mysem_open() may not put files in the same directories as
 * does the host's implementation of sem_open(), so px_ipc_name() may not
 * do the right thing.  The way around this is to specify PX_IPC_NAME=foo
 * (i.e., set the shell's variable) on the command line when executing
 * this program.
 */
/* include main */
#include	"unpipc.h"
#include	"semaphore.h"

#define	NBUFF	 10
#define	SEM_MUTEX	"mutex"	 	/* these are args to px_ipc_name() */
#define	SEM_NEMPTY	"nempty"
#define	SEM_NSTORED	"nstored"

int		nitems;					/* read-only by producer and consumer */
struct {	/* data shared by producer and consumer */
  int	buff[NBUFF];
  mysem_t	*mutex, *nempty, *nstored;
} shared;

void	*produce(void *), *consume(void *);

int
main(int argc, char **argv)
{
	pthread_t	tid_produce, tid_consume;

	if (argc != 2)
		err_quit("usage: prodcons1 <#items>");
	nitems = atoi(argv[1]);

		/* 4create three semaphores */
	shared.mutex = Mysem_open(Px_ipc_name(SEM_MUTEX), O_CREAT | O_EXCL,
							FILE_MODE, 1);
	shared.nempty = Mysem_open(Px_ipc_name(SEM_NEMPTY), O_CREAT | O_EXCL,
							 FILE_MODE, NBUFF);
	shared.nstored = Mysem_open(Px_ipc_name(SEM_NSTORED), O_CREAT | O_EXCL,
							  FILE_MODE, 0);

	Set_concurrency(2);
	Pthread_create(&tid_produce, NULL, produce, NULL);
	Pthread_create(&tid_consume, NULL, consume, NULL);

	Pthread_join(tid_produce, NULL);
	Pthread_join(tid_consume, NULL);

	Mysem_unlink(Px_ipc_name(SEM_MUTEX));
	Mysem_unlink(Px_ipc_name(SEM_NEMPTY));
	Mysem_unlink(Px_ipc_name(SEM_NSTORED));
	exit(0);
}
/* end main */

/* include prodcons */
void *
produce(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		Mysem_wait(shared.nempty);	/* wait for at least 1 empty slot */
		Mysem_wait(shared.mutex);
		shared.buff[i % NBUFF] = i;	/* store i into circular buffer */
		Mysem_post(shared.mutex);
		Mysem_post(shared.nstored);	/* 1 more stored item */
	}
	return(NULL);
}

void *
consume(void *arg)
{
	int		i;

	for (i = 0; i < nitems; i++) {
		Mysem_wait(shared.nstored);		/* wait for at least 1 stored item */
		Mysem_wait(shared.mutex);
		if (shared.buff[i % NBUFF] != i)
			printf("buff[%d] = %d\n", i, shared.buff[i % NBUFF]);
		Mysem_post(shared.mutex);
		Mysem_post(shared.nempty);		/* 1 more empty slot */
	}
	return(NULL);
}
/* end prodcons */
