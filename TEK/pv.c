//< 信号量操作PV原语
#include <sys/sem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>

union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

//< 初始化semnums个信号灯/信号量的值(value)
int I(int semnums, int value)
{
    //创建信号量集
    int semid = semget(IPC_PRIVATE, semnums, IPC_CREAT | IPC_EXCL | 0777);
    if(semid < 0){
        perror("semget faild!");
        return -1;
    }
    union semun un;
    unsigned short *array = 
            (unsigned short *)calloc(semnums, sizeof(unsigned short));

    int i;
    for(i = 0; i < semnums; i ++)
    {
        array[i] = value;
    }
    un.array = array;
    /*
     * 初始化信号集中所有的信号灯的初值0;
     * 0：标示要初始化的所有信号集
    */   
   if (semctl(semid, 0, SETALL, un) < 0){
       perror("semctl error");
       return -1;
   }
   free(array);
   return semid; 

}

//< 对信号量集(semid)中的信号灯(semnum)做P(value)操作
void P(int semid, int semnum, int value)
{
    assert(value >= 0);
    //定义sembuf类型的结构体数组,防止若干个新结构体变量 , ops中有多少个信号量决定
    //防止要操作的信号量、P或V操作
     struct sembuf ops[] = 
                        {{semnum, -value, SEM_UNDO}};
    if(semop(semid, ops, sizeof(ops)/sizeof(struct sembuf)) < 0){
        perror("semop error");
    }

}

//< 对信号量集(semid)中的信号灯(semnum)作V(value)操作
void V(int semid, int semnum, int value)
{     
     assert(value >= 0);
    //定义sembuf类型的结构体数组,防止若干个新结构体变量 , ops中有多少个信号量决定
    //防止要操作的信号量、P或V操作
     struct sembuf ops[] = 
                        {{semnum, -value, SEM_UNDO}};
    if(semop(semid, ops, sizeof(ops)/sizeof(struct sembuf)) < 0){
        perror("semop error");
    }    

}

//< 销毁信号量集
void D(int semid)
{
    if(semctl(semid, 0, IPC_RMID, NULL) < 0){
        perror("semctl error");
    }

}



