include ../Make.defines

PROGS =	incr_pxmutex0 incr_pxmutex1 incr_pxmutex5 \
		incr_pxsem1 incr_pxsem2 incr_pxsem5 incr_pxsem6 \
		incr_svsem1 incr_svsem2 incr_svsem5 incr_svsem6 \
		incr_pxsem7 incr_pxsem8 incr_pxsem9 \
		incr_rwlock1 incr_rwlock2 incr_rwlock5 \
		incr_fcntl1 incr_fcntl5 \
		bw_pipe bw_pxmsg bw_svmsg bw_door \
		bw_sunrpc_client bw_sunrpc_server \
		lat_pipe lat_pxmsg lat_svmsg lat_door \
		lat_sunrpc_client lat_sunrpc_server \
		lat_signal lat_sigwait lat_sigqueue

all:	${PROGS}

incr_pxmutex0:	incr_pxmutex0.o
		${CC} ${CFLAGS} -o $@ incr_pxmutex0.o ${LIBS}

incr_pxmutex1:	incr_pxmutex1.o
		${CC} ${CFLAGS} -o $@ incr_pxmutex1.o ${LIBS}

incr_pxmutex5:	incr_pxmutex5.o
		${CC} ${CFLAGS} -o $@ incr_pxmutex5.o ${LIBS}

incr_pxsem1:	incr_pxsem1.o
		${CC} ${CFLAGS} -o $@ incr_pxsem1.o ${LIBS}

incr_pxsem2:	incr_pxsem2.o
		${CC} ${CFLAGS} -o $@ incr_pxsem2.o ${LIBS}

incr_pxsem5:	incr_pxsem5.o
		${CC} ${CFLAGS} -o $@ incr_pxsem5.o ${LIBS}

incr_pxsem6:	incr_pxsem6.o
		${CC} ${CFLAGS} -o $@ incr_pxsem6.o ${LIBS}

incr_pxsem7:	incr_pxsem7.o
		${CC} ${CFLAGS} -o $@ incr_pxsem7.o ${LIBS}

incr_pxsem8:	incr_pxsem8.o
		${CC} ${CFLAGS} -o $@ incr_pxsem8.o ${LIBS}

incr_pxsem9:	incr_pxsem9.o
		${CC} ${CFLAGS} -o $@ incr_pxsem9.o ${LIBS}

incr_svsem1:	incr_svsem1.o
		${CC} ${CFLAGS} -o $@ incr_svsem1.o ${LIBS}

incr_svsem2:	incr_svsem2.o
		${CC} ${CFLAGS} -o $@ incr_svsem2.o ${LIBS}

incr_svsem5:	incr_svsem5.o
		${CC} ${CFLAGS} -o $@ incr_svsem5.o ${LIBS}

incr_svsem6:	incr_svsem6.o
		${CC} ${CFLAGS} -o $@ incr_svsem6.o ${LIBS}

incr_rwlock1:	incr_rwlock1.o
		${CC} ${CFLAGS} -o $@ incr_rwlock1.o ${LIBS}

incr_rwlock2:	incr_rwlock2.o
		${CC} ${CFLAGS} -o $@ incr_rwlock2.o ${LIBS}

incr_rwlock5:	incr_rwlock5.o
		${CC} ${CFLAGS} -o $@ incr_rwlock5.o ${LIBS}

incr_fcntl1:	incr_fcntl1.o
		${CC} ${CFLAGS} -o $@ incr_fcntl1.o ${LIBS}

incr_fcntl5:	incr_fcntl5.o
		${CC} ${CFLAGS} -o $@ incr_fcntl5.o ${LIBS}

bw_pipe:	bw_pipe.o
		${CC} ${CFLAGS} -o $@ bw_pipe.o ${LIBS}

bw_pxmsg:	bw_pxmsg.o
		${CC} ${CFLAGS} -o $@ bw_pxmsg.o ${LIBS}

bw_svmsg:	bw_svmsg.o
		${CC} ${CFLAGS} -o $@ bw_svmsg.o ${LIBS}

bw_door:	bw_door.o
		${CC} ${CFLAGS} -o $@ bw_door.o ${LIBS} -ldoor

bw_sunrpc.h bw_sunrpc_clnt.c bw_sunrpc_svc.c bw_sunrpc_xdr.c:	bw_sunrpc.x
			rpcgen ${RPCGEN_OPTS} bw_sunrpc.x

bw_sunrpc_clnt.o: bw_sunrpc_clnt.c bw_sunrpc.h

bw_sunrpc_svc.o: bw_sunrpc_svc.c bw_sunrpc.h

bw_sunrpc_client:	bw_sunrpc.h bw_sunrpc_client.o bw_sunrpc_clnt.o bw_sunrpc_xdr.o
		${CC} ${CFLAGS} -o $@ bw_sunrpc_client.o bw_sunrpc_clnt.o \
			bw_sunrpc_xdr.o ${LIBS} ${LIBS_RPC}

bw_sunrpc_server:	bw_sunrpc.h bw_sunrpc_server.o bw_sunrpc_svc.o bw_sunrpc_xdr.o
		${CC} ${CFLAGS} -o $@ bw_sunrpc_server.o bw_sunrpc_svc.o \
			bw_sunrpc_xdr.o ${LIBS} ${LIBS_RPC}

lat_pipe:	lat_pipe.o
		${CC} ${CFLAGS} -o $@ lat_pipe.o ${LIBS}

lat_pxmsg:	lat_pxmsg.o
		${CC} ${CFLAGS} -o $@ lat_pxmsg.o ${LIBS}

lat_svmsg:	lat_svmsg.o
		${CC} ${CFLAGS} -o $@ lat_svmsg.o ${LIBS}

lat_door:	lat_door.o
		${CC} ${CFLAGS} -o $@ lat_door.o ${LIBS} -ldoor

lat_sunrpc.h lat_sunrpc_clnt.c lat_sunrpc_svc.c lat_sunrpc_xdr.c:	lat_sunrpc.x
			rpcgen ${RPCGEN_OPTS} lat_sunrpc.x

lat_sunrpc_clnt.o: lat_sunrpc_clnt.c lat_sunrpc.h

lat_sunrpc_svc.o: lat_sunrpc_svc.c lat_sunrpc.h

lat_sunrpc_client:	lat_sunrpc.h lat_sunrpc_client.o lat_sunrpc_clnt.o lat_sunrpc_xdr.o
		${CC} ${CFLAGS} -o $@ lat_sunrpc_client.o lat_sunrpc_clnt.o \
			lat_sunrpc_xdr.o ${LIBS} ${LIBS_RPC}

lat_sunrpc_server:	lat_sunrpc.h lat_sunrpc_server.o lat_sunrpc_svc.o lat_sunrpc_xdr.o
		${CC} ${CFLAGS} -o $@ lat_sunrpc_server.o lat_sunrpc_svc.o \
			lat_sunrpc_xdr.o ${LIBS} ${LIBS_RPC}

lat_signal:	lat_signal.o
		${CC} ${CFLAGS} -o $@ lat_signal.o ${LIBS}

lat_sigwait:	lat_sigwait.o
		${CC} ${CFLAGS} -o $@ lat_sigwait.o ${LIBS}

lat_sigqueue:	lat_sigqueue.o
		${CC} ${CFLAGS} -o $@ lat_sigqueue.o ${LIBS}

test1:	test1.o
		${CC} ${CFLAGS} -o $@ test1.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES} *_clnt.c *_svc.c *_xdr.c \
			bw_sunrpc.h
