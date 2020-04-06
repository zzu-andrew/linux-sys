include ../Make.defines

PROGS =	ftok ftok1 ftok2

all:	${PROGS}

ftok:	ftok.o
		${CC} ${CFLAGS} -o $@ ftok.o ${LIBS}

ftok1:	ftok1.o
		${CC} ${CFLAGS} -o $@ ftok1.o ${LIBS}

ftok2:	ftok2.o
		${CC} ${CFLAGS} -o $@ ftok2.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
