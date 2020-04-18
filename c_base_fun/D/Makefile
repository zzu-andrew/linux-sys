include ../Makefile.inc

LINUX_EXE = delay div

CFLAGS +=

EXE =  ${LINUX_EXE}

all : ${EXE}


clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation