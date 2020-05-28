c	= Set.c Bag.c
h	= new.h Set.h Object.h
m	= main.c
t	= sets bags

sets	= main.o Set.o
bags	= main.o Bag.o

all:		$t

test::		sets		; sets
test::		bags		; bags

sets:		$(sets)		; $(CC) $(CFLAGS) -o $@ $(sets)
bags:		$(bags)		; $(CC) $(CFLAGS) -o $@ $(bags)

include ../../makefile.$A
