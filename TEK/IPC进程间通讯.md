[TOC]

 ## System V IPC概述

- System V引入了三种高级进程间通信机制

1. 消息队列、共享内存和信号量

- IPC对象(消息队列、共享内存和信号量)存在于内核而不是文件系统中，由用户控制释放(用户管理IPC对象的生命周期)，不像管道的释放由内核控制。
- IPC对象通过其标识来引用和访问，所有的IPC对象在内核空间中唯一性标识ID，在用户空间中的唯一性标识称为Key.

- IPC对象是全局对象，可以通过ipcs，ipcrm等命令来查看或删除
- 每个IPC对象都由get函数创建

1. msgget,shmget,semget，调用get函数时必须指定关键字key

```bash
andrew@andrew-Thurley:/work/linux-sys$ ipcs

--------- 消息队列 -----------
键        msqid      拥有者  权限     已用字节数 消息      

------------ 共享内存段 --------------
键        shmid      拥有者  权限     字节     连接数  状态      
0x00000000 884736     andrew     600        16777216   2                       
0x00000000 786433     andrew     600        524288     2          目标       
0x00000000 983042     andrew     600        524288     2          目标       
0x00000000 655363     andrew     600        524288     2          目标       
0x00000000 1933316    andrew     700        30072      2          目标       
0x00000000 1081349    andrew     600        524288     2          目标       
0x00000000 1409030    andrew     600        524288     2          目标       
0x00000000 1572871    andrew     600        524288     2          目标       
0x00000000 1835016    andrew     600        524288     2          目标       
0x51010013 1638409    andrew     600        1          1                       
0x00000000 1736714    andrew     600        268435456  2          目标       
0x00000000 2031627    andrew     600        524288     2          目标       
0x00000000 2064396    andrew     600        524288     2          目标       
0x00000000 2162701    andrew     600        524288     2          目标       
0x00000000 2195470    andrew     600        4194304    2          目标       
0x00000000 2326544    andrew     600        524288     2          目标       
0x00000000 2424849    andrew     600        524288     2          目标       
0x00000000 2555922    andrew     600        2097152    2          目标       
0x00000000 2850835    andrew     700        222828     2          目标       

--------- 信号量数组 -----------
键        semid      拥有者  权限     nsems     
0x51010012 32768      andrew     600        1 
```

# 消息队列

- 消息队列是内核中的一个链表
- 用户进程将数据传输到内核后，内核重新添加一些如用户ID,组ID，读写进程的ID和优先级等相关信息后并打成一个数据包称为消息
- 允许一个进程或者多个进程往消息队列中写消息和读消息，但一个消息只能被一个进程读取，读取完毕后就自动删除

- 消息队列具有一定的FIFO的特性，消息可以按照顺序发送到队列中，也可以几种不同的方式从队列中读取，每一个消息对垒在内核中用一个唯一的IPC标识ID表示
- 消息队列的实现包括创建和打开队列、发送消息、读取消息和控制消息队列四中操作

## 创建或打开消息队列

```c
#include <sys/msg.h>
int msgget(key_t key, int flag);
返回：成功返回内核中消息队列的标识ID，出错返回-1
```

## 消息控制
```c
#include <sys/msg.h>
int msgctl(int msgid, intcmd, struct msqid_ds *buf);;
返回：成功返回0，出错返回-1
```

## 发送消息

```c
#include <sys/msg.h>
int msgsnd(int msgqid, const void *ptr, size_t nbytes,int flag);
返回：成功返回0，出错返回-1
ptr:
struct mymesg{
    long mytype;
    char mtext[512];
}
```

- nbytes 指定消息的大小，不包括mtype的大小
- mtype指消息的类型，它由一个整数来代表，并且它只能是大于0的整数
- mtext是消息数据本身
- 在linux中，消息的最大长度是4056个字节，其中包括mtype，它占有4个字节
- 结构体mymesg用户可自定义，但第一个成员必须是mytype

##  接收消息

```c
#include <sys/msg.h>
ssize_t msgrcv(int msgqid, void *ptr,size_t nbytes,long type, int flag);
返回：成功返回消息的数据部分长度，出错返回-1
    type : 消息类型
    type == 0 : l获得消息队列中的第一个消息
    type > 0 : 获得消息队列中类型为type的第一个消息
    type < 0 : 获得消息中小于或等于type和绝对值的消息`
```

## 发送消息示例：

```c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

typedef struct{
    long type; //消息类型
    int start; //消息数据本身
    int end;
}MSG;


/**
 *  往消息队列中发送消息
 */

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("usage: %s key \n", argv[0]);
        exit(1);
    }

    key_t key = atoi(argv[1]);
    printf("key: %d\n", key);
    //创建消息队列
    int msq_id;
    if((msq_id = msgget(key, IPC_CREAT | IPC_EXCL | 0777)) < 0)
    {
        perror("msgget error");
    }
    printf("msg id: %d\n", msq_id);


    //定义要发送的消息
    MSG m1 = {4, 4, 400};
    MSG m2 = {2, 2, 200};
    MSG m3 = {1, 1, 100};
    MSG m4 = {6, 6, 600};
    MSG m5 = {6, 60, 6000};


    //发型消息到消息队列
    if(msgsnd(msq_id, &m1, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0){
        perror("msgsnd error");
    }

    if(msgsnd(msq_id, &m2, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0){
        perror("msgsnd error");
    }

    if(msgsnd(msq_id, &m3, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0){
        perror("msgsnd error");
    }

    if(msgsnd(msq_id, &m4, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0){
        perror("msgsnd error");
    }

    if(msgsnd(msq_id, &m5, sizeof(MSG) - sizeof(long), IPC_NOWAIT) < 0){
        perror("msgsnd error");
    }

    //获取发送消息的总数
    struct msqid_ds ds;
    if(msgctl(msq_id, IPC_STAT, &ds) < 0){
        perror("msgctl error");
    }

    printf("msg total : %ld\n", ds.msg_qnum);

    exit(0);
}

```

执行结果

```bash
andrew@andrew-Thurley:/work/linux-sys/TEK$ ./a.out 32
key: 32
msg id: 0
msg total : 5
andrew@andrew-Thurley:/work/linux-sys/TEK$ ipcs -q

--------- 消息队列 -----------
键        msqid      拥有者  权限     已用字节数 消息      
0x00000020 0          andrew     777        40           5           

# 同样的key值发送之后只能发送一次，等待接受之后才能再发送
andrew@andrew-Thurley:/work/linux-sys/TEK$ ./a.out 32
key: 32
msgget error: File exists
msg id: -1
msgsnd error: Invalid argument
msgsnd error: Invalid argument
msgsnd error: Invalid argument
msgsnd error: Invalid argument
msgsnd error: Invalid argument
msgctl error: Invalid argument
msg total : 0
andrew@andrew-Thurley:/work/linux-sys/TEK$ ./a.out 36
key: 36
msg id: 32769
msg total : 5
andrew@andrew-Thurley:/work/linux-sys/TEK$ ipcs -q

--------- 消息队列 -----------
键        msqid      拥有者  权限     已用字节数 消息      
0x00000020 0          andrew     777        40           5           
0x00000024 32769      andrew     777        40           5           

# 删除消息队列
andrew@andrew-Thurley:/work/linux-sys/TEK$ ipcs -q 

--------- 消息队列 -----------
键        msqid      拥有者  权限     已用字节数 消息      
0x00000024 32769      andrew     777        40           5           

andrew@andrew-Thurley:/work/linux-sys/TEK$ ipcrm -q 32769
andrew@andrew-Thurley:/work/linux-sys/TEK$ ipcs -q 

--------- 消息队列 -----------
键        msqid      拥有者  权限     已用字节数 消息 
```

- 说明：消息队列中的消息被接收完之后消息队列还是存在的，由用户删除



# 共享内存

- 共享内存区域是被多个进程共享的一部分物理内存。
- 多个进程都可以把该共享内存映射到自己的虚拟内存空间，所有用户空间的进程若要操作共享内存，都要将其映射到自己的虚拟内存空间中，通过映射的虚拟内存空间地址去操作共享内存，从而达到进程间的数据通信。
- 共享内存是进程间共享数据的一种最快的方法，一个进程向共享内存区域写入数据，共享内存中的所有进程就可以立刻看到其中的内容
- 本身不提供同步机制，可以通过信号量进行同步
- 提升数据处理效率，一种效率最高的IPC机制

- `shmget`创建共享内存函数
- `shmat`函数映射共享内存，将这段创建共享的共享内存映射到具体的进程虚拟内存空间

 ## 创建共享内存

```bash
#include <sys/ipc.h>
#include <sys/shm.h>

int shmget(key_t key, size_t size, int shmflg);
```

## 共享内存控制

```bash
#include <sys/ipc.h>
#include <sys/shm.h>

int shmctl(int shmid, int cmd, struct shmid_ds *buf);
```



## 共享内存映射和解除映射

```bash
#include <sys/types.h>
#include <sys/shm.h>

void *shmat(int shmid, const void *shmaddr, int shmflg);
返回： 成功返回共享内存映射到进程虚拟内存空间中的地址，失败返回-1
int shmdt(const void *shmaddr);
返回： 如果失敗，則返回-1　　
```

- 父子进程通过管道创建共享内存案例

## 共享内存使用示例:

telll.c

```c
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

```

tell.h

```c
#ifndef __TELL_H__
#define __TELL_H__

//管道初始化
extern void init();

//利用管道进行等待
extern void wait_pipe();
//利用管道进行通知
extern void notify_pipe();
//销毁管道
extern void destroy_pipe();

#endif //TELL

```

cal_shm.c

```c
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


```



Makefile

```bash

all:cal_shm

cal_shm: cal_shm.c tell.c
	gcc -o cal_shm -I. tell.c cal_shm.c

```



# 信号量

## 进程间信号量

- 进程信号量本质上就是共享资源的数目，用来控制对共享资源的访问
- 用于进程间资源的互斥和同步
- 每种共享资源对应一个信号量，为了便于大量共享资源的操作引入了信号量集，可对所有的信号量一次性操作。对信号量集中的所有操作可以要求全部陈宫，也可以部分成功。
- 二元信号量(信号灯)值为和
- 对信号量做`PV`操作

## 创建信号量集

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);

返回：成功返回信号量集ID, 出错返回-1
```

- `key`:用户指定的信号量集键值
- `nsems`:信号量集中信号量个数
- `flag`:`IPC_CREAT、IPC_EXECL`等权限的组合

## 信号量集控制

```c
       #include <sys/types.h>
       #include <sys/ipc.h>
       #include <sys/sem.h>

       int semctl(int semid, int semnum, int cmd, ...);

DESCRIPTION
       semctl()  performs the control operation specified by cmd on the System V sema‐
       phore set identified by semid, or on the semnum-th semaphore of that set.  (The
       semaphores in a set are numbered starting at 0.)

       This  function  has  three or four arguments, depending on cmd.  When there are
       four, the fourth has the type union semun.  The  calling  program  must  define
       this union as follows:

           union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
           };

       The semid_ds data structure is defined in <sys/sem.h> as follows:

           struct semid_ds {
               struct ipc_perm sem_perm;  /* Ownership and permissions */
               time_t          sem_otime; /* Last semop time */
               time_t          sem_ctime; /* Last change time */
               unsigned long   sem_nsems; /* No. of semaphores in set */
           };

       The  ipc_perm  structure is defined as follows (the highlighted fields are set‐
       table using IPC_SET):

           struct ipc_perm {
               key_t          __key; /* Key supplied to semget(2) */
               uid_t          uid;   /* Effective UID of owner */
               gid_t          gid;   /* Effective GID of owner */
               uid_t          cuid;  /* Effective UID of creator */
               gid_t          cgid;  /* Effective GID of creator */
               unsigned short mode;  /* Permissions */
               unsigned short __seq; /* Sequence number */
           };
```

- `semid`:信号量集`ID`
- `semnum`: 0表欧式所有信号量操作，信号量编号从开始。
- `val`:防止获取或设置信号量集中某个信号量值
- `buf`:信号量集属性指针
- `array`:放置获取或设置信号量集中所有信号量的值

## 信号量集操作

```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semop(int semid, struct sembuf *sops, size_t nsops);

int semtimedop(int semid, struct sembuf *sops, size_t nsops,
               const struct timespec *timeout);

```

















