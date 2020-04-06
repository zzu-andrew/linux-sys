#============================
#段错误dbg调试方法
#< 将内核转存储设置为无限制
##ulimit -c unlimited 
#
#===========================



CFLAGS = -Wall -O2 -g

EXE_OBJ = segment

SOURCE = segment.c

all: ${EXE_OBJ}
${EXE_OBJ} : ${SOURCE}
	#将内核默认的核心转存储大小0 设置为可以无限大
	#ulimit -c unlimited 因为在Makefile中设置的环境比变量影响不到调用的
	#bash因此需要手动设置才能生效
	@echo 'make sure you had set "ulimit -c unlimited"'
	gcc ${CFLAGS} $< -o $@


clean:
	rm -rf core segment 

