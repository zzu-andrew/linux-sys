
sys_man = libsys_man.a


TLPI_DIR = ..
TLPI_INCL_DIR = ${TLPI_DIR}/include
TLPI_INCL_SOURCE = ${TLPI_DIR}


all : ${sys_man}

${sys_man}: ${TLPI_INCL_SOURCE}
	#gcc -I${TLPI_INCL_DIR} -c ${TLPI_INCL_SOURCE} 
	#ar -rc libsys_man.a inet_sockets.o

clean : 
	${RM} ${sys_man} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
