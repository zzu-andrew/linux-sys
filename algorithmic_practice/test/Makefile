include ../Makefile.inc


EXE = algo_test



TLPI_INCL_SOURCE += $(wildcard *.c)
OBJS  := $(TLPI_INCL_SOURCE:.c=.o)

all : ${EXE}

${EXE}: ${TLPI_INCL_SOURCE}
	echo ${TLPI_INCL_SOURCE} 
	${CC} ${CFLAGS} $^ ${LDLIBS}  -o $@  


clean : 
	${RM}  *.o  ${EXE}

showall :
	@echo ${EXE}
