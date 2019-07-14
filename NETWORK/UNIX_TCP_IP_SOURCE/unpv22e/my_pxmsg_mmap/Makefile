include ../Make.defines

PROGS =	testmq test1 \
		mqcreate mqgetattr mqnotify1 mqreceive mqsend mqunlink
FUNCS = mq_close.o mq_getattr.o mq_notify.o mq_open.o \
		mq_receive.o mq_send.o mq_setattr.o mq_unlink.o

all:	${PROGS}

# My test program.  Argument is a real pathname.

testmq:	testmq.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ testmq.o ${FUNCS} ${LIBS}

# Automatically generated version of testmq that used the system's
# mq_XXX() functions.  Argument is whatever the system takes as a
# Posix IPC name.

test1.c:	testmq.c
		sed -e 's/Mymq_/Mq_/g' \
			-e 's/mymq_/mq_/g' \
			-e 's/mymqd_t/mqd_t/g' \
			-e 's/<pathname>/<name>/' \
			-e '/mqueue.h/d' < testmq.c > test1.c
test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

mqcreate:	mqcreate.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqcreate.o ${FUNCS} ${LIBS}

mqgetattr:	mqgetattr.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqgetattr.o ${FUNCS} ${LIBS}

mqnotify1:	mqnotify1.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqnotify1.o ${FUNCS} ${LIBS}

mqreceive:	mqreceive.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqreceive.o ${FUNCS} ${LIBS}

mqsend:	mqsend.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqsend.o ${FUNCS} ${LIBS}

mqunlink:	mqunlink.o ${FUNCS}
		${CC} ${CFLAGS} -o $@ mqunlink.o ${FUNCS} ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
