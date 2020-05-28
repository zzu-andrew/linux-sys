c	= binary.c Name.c value.c Var.c mathlib.c parse.c
h	= $(c:.c=.h)
r	= Name.r value.r
t	= value

value	= $(c:.c=.o)

all:		$t

test::		value		; echo 'let a = sin(1) + PI' | value

value:		$(value)	; $(CC) $(CFLAGS) -o $@ $(value) -lm $(debug)

include ../../makefile.$A
