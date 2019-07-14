include ../Make.defines

PROGS =	mainpipe mainfifo

all:	${PROGS}

mainpipe:	mainpipe.o client.o server.o mesg_send.o mesg_recv.o
		${CC} ${CFLAGS} -o $@ mainpipe.o client.o server.o \
			mesg_send.o mesg_recv.o ${LIBS}

mainfifo:	mainfifo.o client.o server.o mesg_send.o mesg_recv.o
		${CC} ${CFLAGS} -o $@ mainfifo.o client.o server.o \
			mesg_send.o mesg_recv.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
