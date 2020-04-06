
all:cal_shm  cal_sem vector_fd




cal_shm: cal_shm.c tell.c
	gcc -o cal_shm -I. tell.c cal_shm.c

cal_sem: pv.o
	gcc -o pv.o -I. -c pv.c


vector_fd: vector_fd.c
	gcc -o vector_fd.o -I. -c vector_fd.c

