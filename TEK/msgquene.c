#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>

typedef struct{
    long type; //消息类型
    int start; //消息数据本身
    int end;
}MSG;


//< 消息队列中的消息被接收完之后消息队列还是存在的

/**
 *  往消息队列中发送消息
 */

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("usage: %s key \n", argv[0]);
        exit(1);
    }

    //key_t key = atoi(argv[1]);
   // key_t key = IPC_PRIVATE;
    key_t key = ftok(argv[1], 0);
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


