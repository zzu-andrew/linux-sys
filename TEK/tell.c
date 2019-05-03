//< 使用管道进行同步共享内存的创建
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "tell.h"


//< 管道文件描述符数组
static int fd[2];

//管道初始化
void init()
{
    if(pipe(fd) < 0){
        perror("perror");
    }

}

//利用管道进行等待
void wait_pipe()
{
    char c;
    //管道读写默认是阻塞性的
    if(read(fd[0], &c, 1) < 0){
        perror("wait pipe error");
    }

}

//利用管道进行通知
void notify_pipe()
{
    char c ='c';
    if(write(fd[1], &c, 1) != 1){
        perror("notify pipe error");
    }

}

//销毁管道
void destroy_pipe()
{
    close(fd[0]);
    close(fd[1]);

}








