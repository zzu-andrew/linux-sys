include ../Make.defines

PROGS =	locknone lockfcntl lockopen locknoneubuf lockpxsem locksvsem \
		locklink lockopen2 locksvsemrace1 locksvsemrace2 \
		loopnone loopfcntl loopopen loopnonenonb looppxsem loopsvsem \
		loopfcntlnonb onedaemon \
		test1 test2 test3 test4

all:	${PROGS}

locknone:	lockmain.o locknone.o
		${CC} ${CFLAGS} -o $@ lockmain.o locknone.o ${LIBS}

lockfcntl:	lockmain.o lockfcntl.o
		${CC} ${CFLAGS} -o $@ lockmain.o lockfcntl.o ${LIBS}

lockopen:	lockmain.o lockopen.o
		${CC} ${CFLAGS} -o $@ lockmain.o lockopen.o ${LIBS}

lockopen2:	lockmain.o lockopen2.o
		${CC} ${CFLAGS} -o $@ lockmain.o lockopen2.o ${LIBS}

locknoneubuf:	lockmainubuf.o locknone.o
		${CC} ${CFLAGS} -o $@ lockmainubuf.o locknone.o ${LIBS}

lockpxsem:	lockmain.o lockpxsem.o
		${CC} ${CFLAGS} -o $@ lockmain.o lockpxsem.o ${LIBS}

locksvsem:	lockmain.o locksvsem.o
		${CC} ${CFLAGS} -o $@ lockmain.o locksvsem.o ${LIBS}

locksvsemrace1:	locksvsemrace1.o
		${CC} ${CFLAGS} -o $@ locksvsemrace1.o ${LIBS}

locksvsemrace2:	locksvsemrace2.o
		${CC} ${CFLAGS} -o $@ locksvsemrace2.o ${LIBS}

locklink:	lockmain.o locklink.o
		${CC} ${CFLAGS} -o $@ lockmain.o locklink.o ${LIBS}

loopnone:	loopmain.o locknone.o
		${CC} ${CFLAGS} -o $@ loopmain.o locknone.o ${LIBS}

loopfcntl:	loopmain.o lockfcntl.o
		${CC} ${CFLAGS} -o $@ loopmain.o lockfcntl.o ${LIBS}

loopopen:	loopmain.o lockopen.o
		${CC} ${CFLAGS} -o $@ loopmain.o lockopen.o ${LIBS}

loopnonenonb:	loopmainnonb.o locknone.o
		${CC} ${CFLAGS} -o $@ loopmainnonb.o locknone.o ${LIBS}

loopfcntlnonb:	loopmainnonb.o lockfcntl.o
		${CC} ${CFLAGS} -o $@ loopmainnonb.o lockfcntl.o ${LIBS}

looppxsem:	loopmain.o lockpxsem.o
		${CC} ${CFLAGS} -o $@ loopmain.o lockpxsem.o ${LIBS}

loopsvsem:	loopmain.o locksvsem.o
		${CC} ${CFLAGS} -o $@ loopmain.o locksvsem.o ${LIBS}

onedaemon:	onedaemon.o
		${CC} ${CFLAGS} -o $@ onedaemon.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

test3:	test3.o
		${CC} ${CFLAGS} -o $@ test3.o ${LIBS}

test4:	test4.o
		${CC} ${CFLAGS} -o $@ test4.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
