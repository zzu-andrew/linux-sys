#include "unix_net_public.h"
#include <time.h>




int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	socklen_t			len;
	struct sockaddr_in	servaddr, cliaddr;
	char				buff[MAXLINE];
	time_t				ticks;
    uint16_t client_port = 0; //< 对端口进行初始化，不n初始化的值是不确定的

    //< 创建套接字，用于服务器的监听
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

    //< 清空套接字地址内容
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port        = htons(8560);	/* daytime server */

    //< 将监听套接字与对应的地址和端口号进行绑定
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    //< 监听对应的套接字，并向内核指定最大的队列长度为 LISTENQ  1024
	listen(listenfd, LISTENQ);


	for ( ; ; ) {
		len = sizeof(cliaddr);
        //<  从已连接的(完成三次握手的连接中，取出一个，返回对应的文件描述符)
		connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &len);
        //< 接收的地址是网络字节序，需要使用 inet_ntop 将其转换为对应的点十进制形式
        //< ntohs 将网络字节序的端口转换为主机字节序的  s代表的是short
        
        inet_ntop(AF_INET, &cliaddr.sin_addr, buff, sizeof(buff));
        UNIX_NET_DEBUG("%s\n", (char *)buff);
        client_port = ntohs(cliaddr.sin_port);
        UNIX_NET_DEBUG("client_port = [%d]\n\n", client_port);

        //< time参数为NULL时获取当前时间
        ticks = time(NULL);
        //< 将time函数获取的time_t 类型的时间转换为可读的方式
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        //< 将时间发回客户端
        write(connfd, buff, strlen(buff));
        //< 关闭已连接的套接字
		close(connfd);
	}
}
