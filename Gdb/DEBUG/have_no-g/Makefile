#============================
#段错误dbg调试方法
#< 将内核转存储设置为无限制
##ulimit -c unlimited 
#
#===========================



CFLAGS = -Wall -O2 -g

EXE_OBJ = have_g
EXE_OBJ_G = have_no_g 

SOURCE = have_no_g.c

all: ${EXE_OBJ} ${EXE_OBJ_G}
${EXE_OBJ} : ${SOURCE}
	@echo 'make sure you had set "ulimit -c unlimited"'
	gcc ${CFLAGS} $< -o $@

${EXE_OBJ_G} : ${SOURCE}
	gcc -Wall -O2 $< -o $@


clean:
	rm -rf core ${EXE_OBJ} ${EXE_OBJ_G} 

