/*
 ****************************************************************
 * @brief  进程信号量的PV操作怎样做
 * @note   QQ:564631192
 * @retval None
 *****************************************************************
 */
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <assert.h>


//< 读者和写者共享的资源 
typedef struct{
    int val;
    int semid;
}Storage;

/**
 * @brief  初始化函数
 * @note   
 * @param  *s: 
 * @retval None
 */
void init (Storage *s)
{
    assert(s != NULL);
    //< 创建信号集包含两个信号量
    if((s->semid = semget(IPC_PRIVATE, 2, IPC_CREAT | IPC_EXCL | 0777)) < 0){
        perror("semget errror");
        exit(1);
    }
    //对信号量集中所有的信号量进行初始化
    union semun{
        int val;
        struct semid_ds *ds;
        unsigned short *array;
    };
    union semun un;
    //信号量初值设置为0
    unsigned short array[2] = {0, 0};
    un.array =array;
    if(semctl(s->semid, 0, SETALL, un) < 0){
        perror("semctl error");
        exit(1); 
    }


}

/**
 * @brief  销毁函数
 * @note   
 * @param  *s: 
 * @retval None
 */
void destroy(Storage *s)
{
    assert(s != NULL);
    if(semctl(s->semid,0, IPC_RMID, NULL) < 0){
        perror("semctl error");

        exit(1);
    }

}

/**
 * @brief  _write函数
 * @note   
 * @param  *s: 
 * @param  val: 
 * @retval None
 */
void __write(Storage *s, int val)
{
    //写入数据到Storage
    s->val = val;
    printf("%d write %d \n", getpid(), val);

    //设置0信号量(s1)作v(1)操作
    //做P操作还是V操作取决于数组中的第二个成员变量的值
    
    struct sembuf ops_v[1] = {{0,1, SEM_UNDO}};  //< 0代表 0号信号量, 1代表做v操作

    //设置1号信号量(s2)作P(1)操作
    struct sembuf ops_p[1] = {{1, -1, SEM_UNDO}}; 

    //V(s1)
    if(semop(s->semid, ops_v, 1) < 0){//0号信号量作V(1)操作
        perror("semop error");
    }

    //P(s2)
    if(semop(s->semid, ops_p, 1) < 0){//0号信号量作P(1)操作
        perror("semop error");
    }
}



/**
 * @brief  _read函数
 * @note   
 * @param  *s: 
 * @retval None
 */
void __read(Storage *s)
{
    assert(s != NULL);

    struct sembuf ops_v[1] = {{0,-1, SEM_UNDO}};  
    struct sembuf ops_p[1] = {{1, 1, SEM_UNDO}}; 
   //V(s2)
    if(semop(s->semid, ops_p, 1) < 0){//0号信号量作P(1)操作
        perror("semop error");
    }
    //P(s1);
    if(semop(s->semid, ops_v, 1) < 0){//0号信号量作V(1)操作
        perror("semop error");
    }

    //从Stirage中读取数据
    printf("%d read %d\n, ",getpid(), s->val);
    
}

/**
 * @brief  主函数
 * @note   
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */
int main(int argc, char *argv[])
{

    //将共享资源Storage创建在共享内存中
    int shmid;
    if((shmid =shmget(IPC_PRIVATE, sizeof(Storage), IPC_CREAT|IPC_EXCL|0777)) < 0){
        perror("shmget error");
        exit(1);
    }

    //父进程进行共享内存映射
    Storage *s = (Storage *)shmat(shmid, 0, 0);
    if(s == (Storage *)-1){
        perror("shmat error");
        exit(1);
    }

    //创建信号量集并进行初始化
    init(s);

    pid_t pid;
    pid = fork();


    if(pid < 0)
    {
        perror("fork error");
        exit(1);
    }else if(pid > 0){
        int i = 1;
        for(; i <= 100; i++){
            __write(s, i);
        }
        //等待子进程结束
        wait(0);
        //销毁信号量
        destroy(s);
        /**
         * @  是用来断开与共享内存附加点的地址，禁止本进程访问此片共享内存
         */
        shmdt(s);
        //删除共享内存
        shmctl(shmid, IPC_RMID, NULL);


    }else
    {
        /* code */
        int i = 1;
        for(; i<= 100; i++)
        {
            __read(s);
        }
        //解除共享内存映射，子进程继承父进程共享内存映射的绑定，shmat 函数实现
        shmdt(s);
    }
    

    return 0;
}




