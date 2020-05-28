dir	= c.01 c.02 c.03 c.04 c.05 c.06 \
	  c.07 c.08 c.09 c.10 c.11 c.12 c.13 c.14
x	= ReadMe makefile makefile.* man ooc

all clean depend test:
	set -e; for i in $(dir); do \
	( echo $$i:; cd $$i && $(MAKE) $@ ); done

t	= $$HOME/export/code.tar
tar:
	tar cfv $t $x $(dir)
