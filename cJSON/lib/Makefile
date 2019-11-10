
cJSONLIB = libcjson.a


TLPI_DIR = ..
TLPI_INCL_DIR = ${TLPI_DIR}/include
TLPI_INCL_SOURCE = ${TLPI_DIR}/sockets/inet_sockets.c


all : ${cJSONLIB}

${cJSONLIB}: ${TLPI_INCL_SOURCE}
	gcc -I${TLPI_INCL_DIR} -c ${TLPI_INCL_SOURCE} 
	ar -rc libcjson.a inet_sockets.o

clean : 
	${RM} ${cJSONLIB} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
