include ../modules_make.inc

DB_LIB = libsqlitedb.a



LIB_PATH = .
INCLUDE_DIR = ${TLPI_DIR}/include
TLPI_INCL_SOURCE += $(wildcard $(LIB_PATH)/*.c)

PUB_INC += db_extern.h

OBJS  := $(TLPI_INCL_SOURCE:.c=.o)

all : ${DB_LIB}

${DB_LIB}: ${TLPI_INCL_SOURCE}
	gcc ${CFLAGS} -c ${TLPI_INCL_SOURCE} 
	ar -rc ${DB_LIB} ${OBJS}
	cp -rf ${PUB_INC} ${INCLUDE_DIR}
	cp -rf ${DB_LIB}  ${TLPI_DIR}/libs

clean : 
	${RM} ${DB_LIB} *.o

showall :
	@ echo ${EXE}

#${EXE} : ${TLPI_LIB}		# True as a rough approximation
