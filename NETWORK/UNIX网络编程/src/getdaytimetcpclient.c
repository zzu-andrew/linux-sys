#include "unix_net_public.h"
#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;


    //< 没有指定IP进行报错处理
    if (argc != 2)
    {
        UNIX_NET_DEBUG("usage: <IPaddress>\n");
        exit(1);
    }
    //< AF_INET 通常代表地址族协议  PF_INET 通产代表网络协议族协议
    //< SOCK_STREAM 字节流
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <  0)
    {
        perror("socket error!\n");
    }

    //<  将地址结构体中的数据进行清空处理
    bzero(&servaddr, sizeof(servaddr));
    
    //< 构造结构体
    servaddr.sin_family = AF_INET; //<网际
    servaddr.sin_port = htons(8560); // 没有找到时间服务器使用ssh端口连接自己的电脑测试连 connect函数的实现


    //< 将点十进制地址转换为网络地址
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        perror("inet_pton error  \n");
    }

    //< 使用connect创建连接
    UNIX_NET_DEBUG("connect start\n");
    //< 将指定套接字转化为通用套接字 struct sockaddr类型
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("connect error\n");
    }
    UNIX_NET_DEBUG("connect is end !\n");
    //< 接受服务器的回复数据
    while((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0;
        if(fputs(recvline, stdout) == EOF)
        {
            perror("fputs error\n");
        }
    }

    if (n < 0)
    {
        perror("error exit()");
    }
    
    
    return 0;
}
