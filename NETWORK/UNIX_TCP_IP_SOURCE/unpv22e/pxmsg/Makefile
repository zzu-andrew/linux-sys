include ../Make.defines

PROGS =	mqcreate1 mqcreate mqgetattr \
		mqnotifysig1 mqnotifysig2 mqnotifysig3 mqnotifysig4 mqnotifysig5 \
		mqreceive mqsend mqsysconf mqunlink \
		test1

all:	${PROGS}

mqcreate1:	mqcreate1.o
		${CC} ${CFLAGS} -o $@ mqcreate1.o ${LIBS}

mqcreate:	mqcreate.o
		${CC} ${CFLAGS} -o $@ mqcreate.o ${LIBS}

mqgetattr:	mqgetattr.o
		${CC} ${CFLAGS} -o $@ mqgetattr.o ${LIBS}

mqnotifysig1:	mqnotifysig1.o
		${CC} ${CFLAGS} -o $@ mqnotifysig1.o ${LIBS}

mqnotifysig2:	mqnotifysig2.o
		${CC} ${CFLAGS} -o $@ mqnotifysig2.o ${LIBS}

mqnotifysig3:	mqnotifysig3.o
		${CC} ${CFLAGS} -o $@ mqnotifysig3.o ${LIBS}

mqnotifysig4:	mqnotifysig4.o
		${CC} ${CFLAGS} -o $@ mqnotifysig4.o ${LIBS}

mqnotifysig5:	mqnotifysig5.o
		${CC} ${CFLAGS} -o $@ mqnotifysig5.o ${LIBS}

mqnotifythread1:	mqnotifythread1.o
		${CC} ${CFLAGS} -o $@ mqnotifythread1.o ${LIBS}

mqreceive:	mqreceive.o
		${CC} ${CFLAGS} -o $@ mqreceive.o ${LIBS}

mqsend:	mqsend.o
		${CC} ${CFLAGS} -o $@ mqsend.o ${LIBS}

mqsysconf:	mqsysconf.o
		${CC} ${CFLAGS} -o $@ mqsysconf.o ${LIBS}

mqunlink:	mqunlink.o
		${CC} ${CFLAGS} -o $@ mqunlink.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
