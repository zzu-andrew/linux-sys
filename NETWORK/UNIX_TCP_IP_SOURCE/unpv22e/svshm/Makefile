include ../Make.defines

PROGS =	shmget shmrmid shmread shmreadid shmwrite limits

all:	${PROGS}

shmget:	shmget.o
		${CC} ${CFLAGS} -o $@ shmget.o ${LIBS}

shmrmid:	shmrmid.o
		${CC} ${CFLAGS} -o $@ shmrmid.o ${LIBS}

shmread:	shmread.o
		${CC} ${CFLAGS} -o $@ shmread.o ${LIBS}

shmreadid:	shmreadid.o
		${CC} ${CFLAGS} -o $@ shmreadid.o ${LIBS}

shmwrite:	shmwrite.o
		${CC} ${CFLAGS} -o $@ shmwrite.o ${LIBS}

limits:	limits.o
		${CC} ${CFLAGS} -o $@ limits.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
