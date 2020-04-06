NAME        = sqlex
BASE        = -D_REENTRANT -fPIC -pthread -W -Wall
DEBUG_ON    = -g -D DEBUG
DEBUG_OFF   = -O2
PROFILE_ON  = -pg --profile-arcs --test-coverage
PROFILE_OFF = 
PROFILING   = $(PROFILE_OFF)
DEBUGGING	= $(DEBUG_ON)

A_LIB = $(NAME).a

LIBFILES = util.o
CC       = gcc
CFLAGS   = $(BASE) $(DEBUGGING) $(PROFILING)
LIBS     = ${COMMON} 
LDFLAGS  = -lsqlite3 
AR	     = ar
ARFLAGS	 = cru

all:	static

# Static library (Release)
static:	$(LIBFILES)
	$(AR) $(ARFLAGS) lib$(A_LIB) $(LIBFILES)

.cpp.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<

.c.o:
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $<

clean:
	rm -f ${LIBFILES} ${A_LIB} ${S_LIB}
	rm -f *.o *~ *.so *.a
