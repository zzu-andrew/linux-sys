include ../Makefile.inc

LINUX_EXE = list_liner

EXE =  ${LINUX_EXE}

all : ${EXE}
	graph-easy graph_easy.txt > graph_ascii.txt



clean : 
	${RM} ${EXE} *.o

showall :
	@ echo ${EXE}

${EXE} : ${TLPI_LIB}		# True as a rough approximation
