include ../Make.defines

DIRS =	square1 square2 square3 square4 square5 \
		square6 square7 square8 square9 square10 \
		xdr1 test1

# All this Makefile does is clean all the subdirectories.

all:

clean:
		for i in ${DIRS} ; \
			do (cd $$i; make clean) ; \
		done
		rm -f ${PROGS} ${CLEANFILES} *_clnt.c *_svc.c *_xdr.c square.h
