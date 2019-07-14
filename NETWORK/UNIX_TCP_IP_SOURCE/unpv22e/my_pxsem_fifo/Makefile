include ../Make.defines

PROGS =	prodcons1 testeintr
FUNCS = sem_close.o sem_open.o sem_post.o sem_unlink.o sem_wait.o

all:	${PROGS}

prodcons1:	prodcons1.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ prodcons1.o ${FUNCS} ${LIBS}

testeintr:	testeintr.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ testeintr.o ${FUNCS} ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
