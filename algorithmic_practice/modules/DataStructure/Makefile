include ../modules_make.inc

DS_LIB = libdatastructure.a



LIB_PATH = .
INCLUDE_DIR = ${TLPI_DIR}/include
TLPI_INCL_SOURCE += $(wildcard $(LIB_PATH)/*.c)

PUB_INC += ds_extern.h

OBJS  := $(TLPI_INCL_SOURCE:.c=.o)

all : ${DS_LIB}

${DS_LIB}: ${TLPI_INCL_SOURCE}
	gcc ${CFLAGS} -c ${TLPI_INCL_SOURCE} 
	ar -rc ${DS_LIB} ${OBJS}
	cp -rf ${PUB_INC} ${INCLUDE_DIR}
	cp -rf ${DS_LIB}  ${TLPI_DIR}/libs

clean : 
	${RM} ${DS_LIB} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
