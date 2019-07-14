include ../Make.defines

# incr_map_anon and incr_dev_zero are not in PORGS since they're
# not on all platforms.

PROGS =	incr1 incr2 incr2private incr3 svmsgread \
		test1 test2 test3

all:	${PROGS}

incr1:	incr1.o
		${CC} ${CFLAGS} -o $@ incr1.o ${LIBS}

incr2:	incr2.o
		${CC} ${CFLAGS} -o $@ incr2.o ${LIBS}

incr2private:	incr2private.o
		${CC} ${CFLAGS} -o $@ incr2private.o ${LIBS}

incr3:	incr3.o
		${CC} ${CFLAGS} -o $@ incr3.o ${LIBS}

incr_dev_zero:	incr_dev_zero.o
		${CC} ${CFLAGS} -o $@ incr_dev_zero.o ${LIBS}

incr_map_anon:	incr_map_anon.o
		${CC} ${CFLAGS} -o $@ incr_map_anon.o ${LIBS}

svmsgread:	svmsgread.o
		${CC} ${CFLAGS} -o $@ svmsgread.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

test3:	test3.o
		${CC} ${CFLAGS} -o $@ test3.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
