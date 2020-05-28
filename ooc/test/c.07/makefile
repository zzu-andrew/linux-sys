chapter	= -7

c	= Object.c Point.c Circle.c List.c Queue.c Stack.c
d	= $(c:.c=)
h	= $(c:.c=.h)
m	= points.c circles.c queue.c stack.c
r	= $(c:.c=.r)
t	= $(m:.c=)

points	= points.o Object.o Point.o
circles	= circles.o Object.o Point.o Circle.o
queue	= queue.o Object.o List.o Queue.o
stack	= stack.o Object.o List.o Stack.o

all:		$t

test::		points		; points p
test::		circles		; circles p c
test::		queue		; queue +axel - +is +here . - . - .
test::		stack		; stack +axel - +is +here . - . - .

points:		$(points)	; $(CC) $(CFLAGS) -o $@ $(points)
circles:	$(circles)	; $(CC) $(CFLAGS) -o $@ $(circles)
queue:		$(queue)	; $(CC) $(CFLAGS) -o $@ $(queue)
stack:		$(stack)	; $(CC) $(CFLAGS) -o $@ $(stack)

include ../../makefile.$A
