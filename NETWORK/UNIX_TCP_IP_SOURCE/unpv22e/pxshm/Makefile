include ../Make.defines

PROGS =	shmcreate shmunlink shmread shmwrite test1 test2 test3 \
		client1 server1 client2 server2

all:	${PROGS}

client1:	client1.o
		${CC} ${CFLAGS} -o $@ client1.o ${LIBS}

server1:	server1.o
		${CC} ${CFLAGS} -o $@ server1.o ${LIBS}

client2:	client2.o
		${CC} ${CFLAGS} -o $@ client2.o ${LIBS}

server2:	server2.o
		${CC} ${CFLAGS} -o $@ server2.o ${LIBS}

shmcreate:	shmcreate.o
		${CC} ${CFLAGS} -o $@ shmcreate.o ${LIBS}

shmunlink:	shmunlink.o
		${CC} ${CFLAGS} -o $@ shmunlink.o ${LIBS}

shmread:	shmread.o
		${CC} ${CFLAGS} -o $@ shmread.o ${LIBS}

shmwrite:	shmwrite.o
		${CC} ${CFLAGS} -o $@ shmwrite.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

test3:	test3.o
		${CC} ${CFLAGS} -o $@ test3.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
