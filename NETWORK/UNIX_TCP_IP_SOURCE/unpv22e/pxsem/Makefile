include ../Make.defines

PROGS =	semcreate semgetvalue semwait sempost semunlink \
		prodcons1 prodcons2 prodcons3 prodcons4 \
		deadlock semsysconf testeintr \
		mycat1 mycat2

all:	${PROGS}

semcreate:	semcreate.o
		${CC} ${CFLAGS} -o $@ semcreate.o ${LIBS}

semgetvalue:	semgetvalue.o
		${CC} ${CFLAGS} -o $@ semgetvalue.o ${LIBS}

semwait:	semwait.o
		${CC} ${CFLAGS} -o $@ semwait.o ${LIBS}

sempost:	sempost.o
		${CC} ${CFLAGS} -o $@ sempost.o ${LIBS}

semunlink:	semunlink.o
		${CC} ${CFLAGS} -o $@ semunlink.o ${LIBS}

prodcons1:	prodcons1.o
		${CC} ${CFLAGS} -o $@ prodcons1.o ${LIBS}

prodcons2:	prodcons2.o
		${CC} ${CFLAGS} -o $@ prodcons2.o ${LIBS}

prodcons3:	prodcons3.o
		${CC} ${CFLAGS} -o $@ prodcons3.o ${LIBS}

prodcons4:	prodcons4.o
		${CC} ${CFLAGS} -o $@ prodcons4.o ${LIBS}

mycat1:	mycat1.o
		${CC} ${CFLAGS} -o $@ mycat1.o ${LIBS}

mycat2:	mycat2.o
		${CC} ${CFLAGS} -o $@ mycat2.o ${LIBS}

deadlock:	deadlock.o
		${CC} ${CFLAGS} -o $@ deadlock.o ${LIBS}

semsysconf:	semsysconf.o
		${CC} ${CFLAGS} -o $@ semsysconf.o ${LIBS}

testeintr:	testeintr.o
		${CC} ${CFLAGS} -o $@ testeintr.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
