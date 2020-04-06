include ../Make.defines

PROGS =	test1 testcancel incr_rwlock1
FUNCS = pthread_rwlock_destroy.o pthread_rwlock_init.o \
		pthread_rwlock_rdlock.o pthread_rwlock_tryrdlock.o \
		pthread_rwlock_trywrlock.o pthread_rwlock_unlock.o \
		pthread_rwlock_wrlock.o

all:	${PROGS}

test1:	test1.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ test1.o ${FUNCS} ${LIBS}

testcancel:	testcancel.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ testcancel.o ${FUNCS} ${LIBS}

incr_rwlock1:	incr_rwlock1.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ incr_rwlock1.o ${FUNCS} ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
