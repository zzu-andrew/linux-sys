
unix_net = unix_net_lib.a


UNIX_NET_DIR = ..
TLPI_INCL_DIR = ${UNIX_NET_DIR}/lib
TLPI_INCL_SOURCE = ${UNIX_NET_DIR}/lib/unix_net_public.c


all : ${unix_net}

${unix_net}: ${TLPI_INCL_SOURCE}
	echo "make lib start"
	gcc -I${TLPI_INCL_DIR} -c ${TLPI_INCL_SOURCE} 
	ar -rc unix_net_lib.a unix_net_public.o
	echo "cp unix_net_public.h to inc start"
	cp ./unix_net_public.h ./../inc
	echo "cp end"

clean : 
	${RM} ${unix_net} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
