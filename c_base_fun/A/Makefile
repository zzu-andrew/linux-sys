include ../Makefile.inc

LINUX_EXE = abort abs acos asctime asin assert atan atexit atof atoi atol

CFLAGS +=

EXE =  ${LINUX_EXE}

all : ${EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation