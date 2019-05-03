//< 使用管道进行同步共享内存的创建
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include "tell.h"



int main(int argc, char *argv[])
{
    //创建共享内存
    int shmid;
    if((shmid = shmget(IPC_PRIVATE, 1024, IPC_CREAT | IPC_EXCL | 0777)) < 0){
        perror("shmget error");
        exit(1);
    }
    pid_t pid;
    init(); //初始化管道
    if((pid = fork()) < 0){
        perror("fork error !");
        exit(1);
    }
    else if(pid > 0){
        //进行共享内存映射
        int *pi;
        pi = (int *)shmat(shmid, 0, 0);
        if(pi == (int *)-1){//<因为pi是指针类型的数据
            perror("shmat error");
            exit(1);  
         }
         //往共享内存中写入数据(通过操作映射的地址即可)
        *pi = 100;
        *(pi +1) =200;
        //操作完，解除共享内存映射
        shmdt(pi);
        //< 通知子进程读取数据
        notify_pipe();
        destroy_pipe();
        wait(0);
    }else{// child process
        //< 子进程阻塞，等待父进程往共享内存中写入数据
        wait_pipe();
        //子进程从共享内存中读取数据
        //子进程进行共享内存的映射
        int *pi = (int *)shmat(shmid, 0, 0);
        if(pi == (int *)-1){
            perror("shmat error");
            exit(1);
        }
        printf("start : %d end : %d \n", *pi, *(pi+1));
        //< 读取完数据，解除映射 
        shmdt(pi);
        //< 删除共享内存 共享内存只有一个，在子进程和父进程中只有一个
        shmctl(shmid, IPC_RMID, NULL);

        destroy_pipe();

    }

    




    exit(0);
}








