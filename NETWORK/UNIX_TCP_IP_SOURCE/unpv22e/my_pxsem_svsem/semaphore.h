/* include semaphoreh */
	/* 4the fundamental datatype */
typedef struct {
  int	sem_semid;		/* the System V semaphore ID */
  int	sem_magic;		/* magic number if open */
} mysem_t;

#define	SEM_MAGIC	0x45678923

#ifdef	SEM_FAILED
#undef	SEM_FAILED
#define	SEM_FAILED	((mysem_t *)(-1))	/* avoid compiler warnings */
#endif

#ifndef	SEMVMX
#define	SEMVMX	32767		/* historical System V max value for sem */
#endif
/* end semaphoreh */

	/* 4our functions */
int		 mysem_close(mysem_t *);
int		 mysem_getvalue(mysem_t *, int *);
mysem_t	*mysem_open(const char *, int, ... );
int		 mysem_post(mysem_t *);
int		 mysem_trywait(mysem_t *);
int		 mysem_unlink(const char *);
int		 mysem_wait(mysem_t *);

	/* 4and the corresponding wrapper functions */
void	 Mysem_close(mysem_t *);
void	 Mysem_getvalue(mysem_t *, int *);
mysem_t	*Mysem_open(const char *, int, ... );
void	 Mysem_post(mysem_t *);
int		 Mysem_trywait(mysem_t *);
void	 Mysem_unlink(const char *);
void	 Mysem_wait(mysem_t *);
