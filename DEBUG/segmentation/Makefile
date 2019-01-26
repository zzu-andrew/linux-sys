#============================
#段错误dbg调试方法
#< 将内核转存储设置为无限制
#ulimit -c unlimited 
#
#===========================


all: segment
segment : segment.c
	#将内核默认的核心转存储大小0 设置为可以无限大
	ulimit -c unlimited
	gcc -g $< -o $@


clean:
	rm -rf core segment 

