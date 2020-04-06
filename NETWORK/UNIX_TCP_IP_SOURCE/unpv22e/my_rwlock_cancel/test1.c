#include	"unpipc.h"
#include	"pthread_rwlock.h"

#define	MAXNTHREADS	100

void	*reader(void *), *writer(void *);

int		nloop = 1000, nreaders = 6, nwriters = 4;

struct {
  pthread_rwlock_t	rwlock;
  pthread_mutex_t	rcountlock;
  int				nreaders;
  int				nwriters;
} shared = { PTHREAD_RWLOCK_INITIALIZER, PTHREAD_MUTEX_INITIALIZER };

int
main(int argc, char **argv)
{
	int		c, i;
	pthread_t	tid_readers[MAXNTHREADS], tid_writers[MAXNTHREADS];

	while ( (c = Getopt(argc, argv, "n:r:w:")) != -1) {
		switch (c) {
		case 'n':
			nloop = atoi(optarg);
			break;

		case 'r':
			nreaders = atoi(optarg);
			break;

		case 'w':
			nwriters = atoi(optarg);
			break;
		}
	}
	if (optind != argc)
		err_quit("usage: test1 [-n #loops ] [ -r #readers ] [ -w #writers ]");

		/* 4create all the reader and writer threads */
	Set_concurrency(nreaders + nwriters);
	for (i = 0; i < nreaders; i++)
		Pthread_create(&tid_readers[i], NULL, reader, NULL);
	for (i = 0; i < nwriters; i++)
		Pthread_create(&tid_writers[i], NULL, writer, NULL);

		/* wait for all the threads to complete */
	for (i = 0; i < nreaders; i++)
		Pthread_join(tid_readers[i], NULL);
	for (i = 0; i < nwriters; i++)
		Pthread_join(tid_writers[i], NULL);

	exit(0);
}

void *
reader(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		pthread_rwlock_rdlock(&shared.rwlock);

		pthread_mutex_lock(&shared.rcountlock);
		shared.nreaders++;	/* shared by all readers; must protect */
		pthread_mutex_unlock(&shared.rcountlock);

		if (shared.nwriters > 0)
			err_quit("reader: %d writers found", shared.nwriters);

		pthread_mutex_lock(&shared.rcountlock);
		shared.nreaders--;	/* shared by all readers; must protect */
		pthread_mutex_unlock(&shared.rcountlock);

		pthread_rwlock_unlock(&shared.rwlock);
	}
	return(NULL);
}

void *
writer(void *arg)
{
	int		i;

	for (i = 0; i < nloop; i++) {
		pthread_rwlock_wrlock(&shared.rwlock);
		shared.nwriters++;	/* only one writer; need not protect */

		if (shared.nwriters > 1)
			err_quit("writer: %d writers found", shared.nwriters);
		if (shared.nreaders > 0)
			err_quit("writer: %d readers found", shared.nreaders);

		shared.nwriters--;	/* only one writer; need not protect */
		pthread_rwlock_unlock(&shared.rwlock);
	}
	return(NULL);
}
