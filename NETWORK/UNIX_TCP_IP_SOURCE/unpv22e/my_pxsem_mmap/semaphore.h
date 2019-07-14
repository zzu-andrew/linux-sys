/* include semaphoreh */
	/* 4the fundamental datatype */
typedef struct {
  pthread_mutex_t	sem_mutex;	/* lock to test and set semaphore value */
  pthread_cond_t	sem_cond;	/* for transition from 0 to nonzero */
  unsigned int		sem_count;	/* the actual semaphore value */
  int				sem_magic;	/* magic number if open */
} mysem_t;

#define	SEM_MAGIC	0x67458923

#ifdef	SEM_FAILED
#undef	SEM_FAILED
#define	SEM_FAILED	((mysem_t *)(-1))	/* avoid compiler warnings */
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
