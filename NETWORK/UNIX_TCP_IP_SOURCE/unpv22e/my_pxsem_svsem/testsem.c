/*
 * This is a test program for my semaphore functions.
 */
/* include main */
#include	"unpipc.h"
#include	"semaphore.h"

#define	SEM1	"sem1"	 	/* these are args to px_ipc_name() */
#define	SEM2	"sem2"
#define	SEM3	"sem3"
#define	SEM4	"sem4"
#define	SEM5	"sem5"
#define	MAX_NTHREADS	 1000
#define	MAX_NSEMS	 	 1000

mysem_t	*sem[MAX_NSEMS];
int		nsems, nthreads, nwaits, initval;

int
main(int argc, char **argv)
{
	int		i, val;
	void	*doit(void *);
	char	name[255];
	pthread_t	tid[MAX_NTHREADS];

	if (argc != 4)
		err_quit("usage: testmysem <#semaphores> <#threads> <initvalue>");
	nsems = min(atoi(argv[1]), MAX_NTHREADS);
	nthreads = min(atoi(argv[2]), MAX_NTHREADS);
	if ( (initval = atoi(argv[3])) == 0)
		initval = Sysconf(_SC_SEM_VALUE_MAX);
	nwaits = initval / nthreads;
	printf("initval = %d, #waits = %d, final values should be %d\n",
			initval, nwaits, initval - (nwaits * nthreads));

		/* 4delete, just in case they're left around */
	for (i = 0; i < nsems; i++) {
		snprintf(name, sizeof(name), "sem%d", i);
		mysem_unlink(Px_ipc_name(name));	/* ignore error */
	}

	Set_concurrency(nthreads);
	for (i = 0; i < nthreads; i++)
		Pthread_create(&tid[i], NULL, doit, NULL);

	for (i = 0; i < nthreads; i++)
		Pthread_join(tid[i], NULL);

	for (i = 0; i < nsems; i++) {
		Mysem_getvalue(sem[i], &val);
		printf("SEM%d = %d\n", i, val);
	}

	for (i = 0; i < nsems; i++) {
		snprintf(name, sizeof(name), "sem%d", i);
		Mysem_unlink(Px_ipc_name(name));
	}
	exit(0);
}
/* end main */

void *
doit(void *arg)
{
	int		i, j;
	char	name[255];

	/*
	 * Each thread tries to create the semaphores (without O_EXCL) to
	 * try and hit any possible race conditions in mysem_open().
	 */

	for (i = 0; i < nsems; i++) {
		snprintf(name, sizeof(name), "sem%d", i);
		sem[i] = Mysem_open(Px_ipc_name(name), O_CREAT, FILE_MODE, initval);
	}

		/* 4decrement each semaphore "nwaits" times, then terminate */
	for (i = 0; i < nwaits; i++) {
		for (j = 0; j < nsems; j++)
			Mysem_wait(sem[j]);
	}
	return(NULL);
}
