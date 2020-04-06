/* include lockh */
#ifndef	__pthread_rwlock_h
#define	__pthread_rwlock_h

typedef struct {
  pthread_mutex_t	rw_mutex;		/* basic lock on this struct */
  pthread_cond_t	rw_condreaders;	/* for reader threads waiting */
  pthread_cond_t	rw_condwriters;	/* for writer threads waiting */
  int				rw_magic;		/* for error checking */
  int				rw_nwaitreaders;/* the number waiting */
  int				rw_nwaitwriters;/* the number waiting */
  int				rw_refcount;
	/* 4-1 if writer has the lock, else # readers holding the lock */
} pthread_rwlock_t;

#define	RW_MAGIC	0x19283746

	/* 4following must have same order as elements in struct above */
#define	PTHREAD_RWLOCK_INITIALIZER	{ PTHREAD_MUTEX_INITIALIZER, \
			PTHREAD_COND_INITIALIZER, PTHREAD_COND_INITIALIZER, \
			RW_MAGIC, 0, 0, 0 }

typedef	int		pthread_rwlockattr_t;	/* dummy; not supported */

	/* 4function prototypes */
int		pthread_rwlock_destroy(pthread_rwlock_t *);
int		pthread_rwlock_init(pthread_rwlock_t *, pthread_rwlockattr_t *);
int		pthread_rwlock_rdlock(pthread_rwlock_t *);
int		pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int		pthread_rwlock_trywrlock(pthread_rwlock_t *);
int		pthread_rwlock_unlock(pthread_rwlock_t *);
int		pthread_rwlock_wrlock(pthread_rwlock_t *);

	/* 4and our wrapper functions */
void	Pthread_rwlock_destroy(pthread_rwlock_t *);
void	Pthread_rwlock_init(pthread_rwlock_t *, pthread_rwlockattr_t *);
void	Pthread_rwlock_rdlock(pthread_rwlock_t *);
int		Pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int		Pthread_rwlock_trywrlock(pthread_rwlock_t *);
void	Pthread_rwlock_unlock(pthread_rwlock_t *);
void	Pthread_rwlock_wrlock(pthread_rwlock_t *);

#endif	__pthread_rwlock_h
/* include lockh */
