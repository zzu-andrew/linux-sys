chapter	= -9

c	= Object.c Point.c Circle.c List.c
d	= $(c:.c=)
h	= $(c:.c=.h)
m	= circles.c list.c
r	= $(c:.c=.r)
t	= $(m:.c=)

circles	= circles.o Object.o Point.o Circle.o
list	= list.o Object.o List.o Point.o Circle.o

all:		$t

test::		circles		;  circles p c
test::		list		;- list + +c +p . - 1234
test::		list		;- list axel

circles:	$(circles)	; $(CC) $(CFLAGS) -o $@ $(circles)
list:		$(list)		; $(CC) $(CFLAGS) -o $@ $(list)

include ../../makefile.$A
