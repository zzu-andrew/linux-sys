BASE        = -D_REENTRANT -fPIC -pthread -W -Wall
DEBUG_ON    = -g -D DEBUG
DEBUG_OFF   = -O2
PROFILE_ON  = -pg --profile-arcs --test-coverage
PROFILE_OFF = 
PROFILING   = $(PROFILE_OFF)
DEBUGGING	= $(DEBUG_ON)

PROGS  = func aggregate strict_typing collate
COMMON = ../common/libsqlex.a  ../common/libpcre.a
CC     = gcc
CFLAGS = $(BASE) $(DEBUGGING) $(PROFILING)
LIBS   = ${COMMON} -lsqlite3 

all:	${PROGS} 

political:	political.o 
	$(CC) $(LDFLAGS) -o political political.o $(LIBS) -lm

func:	func.o 
	$(CC) $(LDFLAGS) -o func func.o $(LIBS)

collate:	collate.o oracle_date.o
	$(CC) $(LDFLAGS) -o collate collate.o oracle_date.o $(LIBS)

aggregate:	aggregate.o 
	$(CC) $(LDFLAGS) -o aggregate aggregate.o $(LIBS)

strict_typing:	strict_typing.o 
	$(CC) $(LDFLAGS) -o strict_typing strict_typing.o $(LIBS)

clean:
		rm -f ${PROGS} ${CLEANFILES}
		rm -f *.o *~ *.so *.a

# Allow core files to be dumped
core:
	ulimit -c 1000000

.cpp.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<

.c.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<
