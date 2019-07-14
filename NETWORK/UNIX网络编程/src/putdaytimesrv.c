#include "unix_net_public.h"


int
main(int argc, char **argv)
{
	int					listenfd, connfd;
	struct sockaddr_in	servaddr;
	char				buff[MAXLINE];
	time_t				ticks;

    //< 创建套接字，文件描述符
	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family      = AF_INET;
    //< 监听所有的笛子， Address to accept any incoming messages. 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //< 今天端口 13 
	servaddr.sin_port        = htons(8560);	/* daytime server */

    //< 绑定套接字，以及端口
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

    //< 监听套接字
	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        //< 服务端通过close关闭与客户端的连接
        //< 该调用引起正常的四次挥手的过程
        
		close(connfd);
	}
}
