include ../Make.defines

PROGS =	test1 test2 test3

all:	${PROGS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

test3:	test3.o
		${CC} ${CFLAGS} -o $@ test3.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
