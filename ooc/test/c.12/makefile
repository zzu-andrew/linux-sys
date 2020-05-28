chapter	= -11

c	= Object.c Node.c Symbol.c Symtab.c
d	= $(c:.c=)
h	= $(c:.c=.h) binary.h parse.h
m	= binary.c parse.c
r	= $(c:.c=.r)
t	= value

value	= parse.o Object.o Node.o Symbol.o Symtab.o binary.o

all:		$t

test::		value		; echo 'let a = sin(1) + PI' | value
test::		value		; { echo 'def sqr = $$ * $$'; \
							echo 'def one = sqr(sin($$)) + sqr(cos($$))'; \
						    echo 'let n = one(10)'; \
							echo save; } | value
test::		value		; { echo load; \
							echo 'n + one(20)'; } | value

value:		$(value)	; nm -p $(value) | munch > classes.c
						  $(CC) $(CFLAGS) -o $@ $(value) classes.c -lm $(debug)

include ../../makefile.$A
