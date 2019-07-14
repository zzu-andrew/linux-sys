include ../Make.defines

PROGS =	mainpipe mainpopen mainfifo \
		client_fifo server_fifo pipeconf test1 test2 fduplex

all:	${PROGS}

mainpipe:	mainpipe.o client.o server.o
		${CC} ${CFLAGS} -o $@ mainpipe.o client.o server.o ${LIBS}

mainpopen:	mainpopen.o
		${CC} ${CFLAGS} -o $@ mainpopen.o ${LIBS}

mainfifo:	mainfifo.o client.o server.o
		${CC} ${CFLAGS} -o $@ mainfifo.o client.o server.o ${LIBS}

client_fifo:	client_main.o client.o
		${CC} ${CFLAGS} -o $@ client_main.o client.o ${LIBS}

server_fifo:	server_main.o server.o
		${CC} ${CFLAGS} -o $@ server_main.o server.o ${LIBS}

pipeconf:	pipeconf.o
		${CC} ${CFLAGS} -o $@ pipeconf.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

test2:	test2.o
		${CC} ${CFLAGS} -o $@ test2.o ${LIBS}

fduplex:	fduplex.o
		${CC} ${CFLAGS} -o $@ fduplex.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
