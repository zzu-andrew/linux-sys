include ../Make.defines

PROGS =	semcreate semrmid semgetvalues semsetvalues semops semopsid \
		initval limits

all:	${PROGS}

semcreate:	semcreate.o
		${CC} ${CFLAGS} -o $@ semcreate.o ${LIBS}

semrmid:	semrmid.o
		${CC} ${CFLAGS} -o $@ semrmid.o ${LIBS}

semgetvalues:	semgetvalues.o
		${CC} ${CFLAGS} -o $@ semgetvalues.o ${LIBS}

semsetvalues:	semsetvalues.o
		${CC} ${CFLAGS} -o $@ semsetvalues.o ${LIBS}

semops:	semops.o
		${CC} ${CFLAGS} -o $@ semops.o ${LIBS}

semopsid:	semopsid.o
		${CC} ${CFLAGS} -o $@ semopsid.o ${LIBS}

initval:	initval.o
		${CC} ${CFLAGS} -o $@ initval.o ${LIBS}

limits:	limits.o
		${CC} ${CFLAGS} -o $@ limits.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
