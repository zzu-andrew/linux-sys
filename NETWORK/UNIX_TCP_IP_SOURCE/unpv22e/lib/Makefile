include ../Make.defines

# Following required by Solaris 2.x for Posix version of sigwait().
CFLAGS += -D_POSIX_PTHREAD_SEMANTICS

all:	${LIB_OBJS}
		ar rv ${LIBUNPIPC_NAME} $?
		${RANLIB} ${LIBUNPIPC_NAME}

clean:
		rm -f ${PROGS} ${CLEANFILES}
