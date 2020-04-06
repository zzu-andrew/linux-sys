#============================
#< 将内核转存储设置为无限制
##ulimit -c unlimited 
#
#===========================



CFLAGS = -Wall -O2 -g

EXE_OBJ = watch

SOURCE = watch.c

all: ${EXE_OBJ}
${EXE_OBJ} : ${SOURCE}
	@echo 'make sure you had set "ulimit -c unlimited"'
	gcc ${CFLAGS} $< -o $@


clean:
	rm -rf core segment 

