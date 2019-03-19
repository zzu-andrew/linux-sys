/**
 *   int pipe(int fd[2]);
 * 返回： 成功返回0，出错返回-1
 */

/**
 *  两个文件描述符数组
 * fd[0]为pipe的读端
 * fd[1]为pipe的写端
 * fd[0]用于读取管道
 * fd[1]用于写入管道
 */

/**
 * @brief  父进程通过管道传输两个数据给子进程
 * @note   由子进程负责从管道中读取并输出
 * @param  argc: 
 * @param  *argv[]: 
 * @retval 
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd[2];
    //创建管道
    if (pipe(fd) < 0)
    {
        perror("pipe error !!!");
        exit(1);
    }

    pid_t  pid;
    if ((pid = fork()) < 0)
    {
       perror("fork error!");
       exit(1); 
    }
    else if (pid > 0)
    {
        //parent process
        close(fd[0]);
        int start = 0, end= 100;
        if (write (fd[1], &start, sizeof(start)) != sizeof(int))
        {
            perror("write error !");
            exit(1);
        }
        if (write (fd[1], &end, sizeof(end)) != sizeof(int))
        {
            perror("write error !");
            exit(1);
        }
        close(fd[1]);
    }
    else
    {
        /* child process */
        close(fd[1]); //子进程进行读取数据，关闭写入文件描述符
        int start, end;
        if (read(fd[0], &start, sizeof(int)) < 0)
        {
            perror("read error!");
            exit(1);
        }
        if (read(fd[0], &end, sizeof(int)) < 0)
        {
            perror("read error!");
            exit(1);
        }
        close(fd[0]);
        printf("start = %d, end = %d\n", start, end);
    }
    




    exit(0);
}




