include ../Make.defines

PROGS =	read write opt1z opt1 opt2 opt2z

all:	${PROGS}

data.h data_xdr.c:	data.x
			rpcgen -C data.x

read:	data.h read.o data_xdr.o
			${CC} ${CFLAGS} -o $@ read.o data_xdr.o ${LIBS} ${LIBS_RPC}

write:	data.h write.o data_xdr.o
			${CC} ${CFLAGS} -o $@ write.o data_xdr.o ${LIBS} ${LIBS_RPC}

example.h example_xdr.c:	example.x
			rpcgen -C example.x

example:	example.h example.o example_xdr.o
			${CC} ${CFLAGS} -o $@ example.o example_xdr.o ${LIBS} ${LIBS_RPC}

opt1.h opt1_xdr.c:	opt1.x
			rpcgen -C opt1.x

opt1z:	opt1.h opt1z.o opt1_xdr.o
			${CC} ${CFLAGS} -o $@ opt1z.o opt1_xdr.o ${LIBS} ${LIBS_RPC}

opt1:	opt1.h opt1.o opt1_xdr.o
			${CC} ${CFLAGS} -o $@ opt1.o opt1_xdr.o ${LIBS} ${LIBS_RPC}

opt2.h opt2_xdr.c:	opt2.x
			rpcgen -C opt2.x

opt2z:	opt2.h opt2z.o opt2_xdr.o
			${CC} ${CFLAGS} -o $@ opt2z.o opt2_xdr.o ${LIBS} ${LIBS_RPC}

opt2:	opt2.h opt2.o opt2_xdr.o
			${CC} ${CFLAGS} -o $@ opt2.o opt2_xdr.o ${LIBS} ${LIBS_RPC}

clean:
		rm -f ${PROGS} ${CLEANFILES} *_clnt.c *_svc.c *_xdr.c data.h example.h
