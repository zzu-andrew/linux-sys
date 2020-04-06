include ../Makefile.inc

sys_man = libsys_man.a


TLPI_DIR = ..
LIB_PATH = .
INCLUDE_DIR = ${TLPI_DIR}/include
TLPI_INCL_SOURCE += $(wildcard $(LIB_PATH)/*.c)

PUB_INC += public_lib.h

OBJS  := $(TLPI_INCL_SOURCE:.c=.o)

all : ${sys_man}

${sys_man}: ${TLPI_INCL_SOURCE}
	gcc ${CFLAGS} -c ${TLPI_INCL_SOURCE} 
	ar -rc libsys_man.a ${OBJS}
	cp -rf ${PUB_INC} ${INCLUDE_DIR}

clean : 
	${RM} ${sys_man} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
