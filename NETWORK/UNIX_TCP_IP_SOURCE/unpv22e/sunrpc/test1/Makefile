include ../Make.defines

PROGS =	data

all:	${PROGS}

data.h data_xdr.c:	data.x
			rpcgen -C data.x

data:	data.h main.o data_xdr.o
			${CC} ${CFLAGS} -o $@ main.o data_xdr.o ${LIBS} ${LIBS_RPC}

clean:
		rm -f ${PROGS} ${CLEANFILES} *_clnt.c *_svc.c *_xdr.c data.h
