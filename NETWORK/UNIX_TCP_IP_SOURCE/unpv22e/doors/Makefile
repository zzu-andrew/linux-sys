include ../Make.defines

# incr_map_anon and incr_dev_zero are not in PORGS since they're
# not on all platforms.

PROGS =	client1 server1 client2 server2 client3 server3 client4 server4 \
		client5 server5 client6 server6 client7 server7 client8 server8 \
		client9 server9 \
		clientintr1 serverintr1 clientintr2 serverintr2 \
		clientintr3 serverintr3 clientintr4 serverintr4 \
		clientfd1 serverfd1 \
		clientunref1 serverunref1 clientunref2 serverunref2 \
		tclient1 tserver1 \
		doorinfo

all:	${PROGS}

doorinfo:	doorinfo.o
		${CC} ${CFLAGS} -o $@ doorinfo.o ${LIBS} -ldoor

client1:	client1.o
		${CC} ${CFLAGS} -o $@ client1.o ${LIBS} -ldoor

server1:	server1.o
		${CC} ${CFLAGS} -o $@ server1.o ${LIBS} -ldoor

client2:	client2.o
		${CC} ${CFLAGS} -o $@ client2.o ${LIBS} -ldoor

server2:	server2.o
		${CC} ${CFLAGS} -o $@ server2.o ${LIBS} -ldoor

client3:	client3.o
		${CC} ${CFLAGS} -o $@ client3.o ${LIBS} -ldoor

server3:	server3.o
		${CC} ${CFLAGS} -o $@ server3.o ${LIBS} -ldoor

client4:	client4.o
		${CC} ${CFLAGS} -o $@ client4.o ${LIBS} -ldoor

server4:	server4.o
		${CC} ${CFLAGS} -o $@ server4.o ${LIBS} -ldoor

client5:	client5.o
		${CC} ${CFLAGS} -o $@ client5.o ${LIBS} -ldoor

server5:	server5.o
		${CC} ${CFLAGS} -o $@ server5.o ${LIBS} -ldoor

client6:	client6.o
		${CC} ${CFLAGS} -o $@ client6.o ${LIBS} -ldoor

server6:	server6.o
		${CC} ${CFLAGS} -o $@ server6.o ${LIBS} -ldoor

client7:	client7.o
		${CC} ${CFLAGS} -o $@ client7.o ${LIBS} -ldoor

server7:	server7.o
		${CC} ${CFLAGS} -o $@ server7.o ${LIBS} -ldoor -lm

client8:	client8.o
		${CC} ${CFLAGS} -o $@ client8.o ${LIBS} -ldoor

server8:	server8.o
		${CC} ${CFLAGS} -o $@ server8.o ${LIBS} -ldoor -lm

client9:	client9.o
		${CC} ${CFLAGS} -o $@ client9.o ${LIBS} -ldoor

server9:	server9.o
		${CC} ${CFLAGS} -o $@ server9.o ${LIBS} -ldoor -lm

clientunref1:	clientunref1.o
		${CC} ${CFLAGS} -o $@ clientunref1.o ${LIBS} -ldoor

serverunref1:	serverunref1.o
		${CC} ${CFLAGS} -o $@ serverunref1.o ${LIBS} -ldoor -lm

clientunref2:	clientunref2.o
		${CC} ${CFLAGS} -o $@ clientunref2.o ${LIBS} -ldoor

serverunref2:	serverunref2.o
		${CC} ${CFLAGS} -o $@ serverunref2.o ${LIBS} -ldoor -lm

clientintr1:	clientintr1.o
		${CC} ${CFLAGS} -o $@ clientintr1.o ${LIBS} -ldoor

serverintr1:	serverintr1.o
		${CC} ${CFLAGS} -o $@ serverintr1.o ${LIBS} -ldoor -lm

clientintr2:	clientintr2.o
		${CC} ${CFLAGS} -o $@ clientintr2.o ${LIBS} -ldoor

serverintr2:	serverintr2.o
		${CC} ${CFLAGS} -o $@ serverintr2.o ${LIBS} -ldoor -lm

clientintr3:	clientintr3.o
		${CC} ${CFLAGS} -o $@ clientintr3.o ${LIBS} -ldoor

serverintr3:	serverintr3.o
		${CC} ${CFLAGS} -o $@ serverintr3.o ${LIBS} -ldoor -lm

clientintr4:	clientintr4.o
		${CC} ${CFLAGS} -o $@ clientintr4.o ${LIBS} -ldoor

serverintr4:	serverintr4.o
		${CC} ${CFLAGS} -o $@ serverintr4.o ${LIBS} -ldoor -lm

clientfd1:	clientfd1.o
		${CC} ${CFLAGS} -o $@ clientfd1.o ${LIBS} -ldoor

serverfd1:	serverfd1.o
		${CC} ${CFLAGS} -o $@ serverfd1.o ${LIBS} -ldoor

tclient1:	tclient1.o
		${CC} ${CFLAGS} -o $@ tclient1.o ${LIBS} -ldoor

tserver1:	tserver1.o
		${CC} ${CFLAGS} -o $@ tserver1.o ${LIBS} -ldoor

clean:
		rm -f ${PROGS} ${CLEANFILES}
