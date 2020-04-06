BASE        = -D_REENTRANT -fPIC -pthread -W -Wall
DEBUG_ON    = -g -D DEBUG
DEBUG_OFF   = -O2
PROFILE_ON  = -pg --profile-arcs --test-coverage
PROFILE_OFF = 
PROFILING   = $(PROFILE_OFF)
DEBUGGING	= $(DEBUG_ON)

PROGS  = create select exec mprintf parameters authorizer
COMMON = util.o
CC     = gcc
CFLAGS = $(BASE) $(DEBUGGING) $(PROFILING)
LIBS   = ${COMMON} -lsqlite3 

all:	${PROGS} 

create:	create.o ${COMMON} 
	$(CC) $(LDFLAGS) -o create create.o $(LIBS)

select:	select.o ${COMMON} 
	$(CC) $(LDFLAGS) -o select select.o $(LIBS)

exec:	exec.o ${COMMON} 
	$(CC) $(LDFLAGS) -o exec exec.o $(LIBS)

mprintf:	mprintf.o ${COMMON} 
	$(CC) $(LDFLAGS) -o mprintf mprintf.o $(LIBS)

parameters:	parameters.o ${COMMON} 
	$(CC) $(LDFLAGS) -o parameters parameters.o $(LIBS)

authorizer:	authorizer.o ${COMMON} 
	$(CC) $(LDFLAGS) -o authorizer authorizer.o $(LIBS)

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
