/**
 * @brief  getdaytimeclientv6
 * @note   使用IPv6的形式获取时间信息　
 */
#include "unix_net_public.h"

/**
 * ( I'm just a cow, not a great thinker ... )
 -----------------------------------------
        o   ^__^
         o  (**)\_______
            (__)\       )\/\
             U  ||----w |
                ||     ||
 
 */

int main(int argc, char **argv)
{
	int					sockfd, n;
	struct sockaddr_in6	servaddr;
	char				recvline[MAXLINE + 1];

	if (argc != 2)
		UNIX_NET_DEBUG("usage: a.out <IPaddress>");

    //< 使用网际协议  字节流的形式创建 socket句柄
	if ( (sockfd = socket(AF_INET6, SOCK_STREAM, 0)) < 0)
		UNIX_NET_DEBUG("socket error");

	bzero(&servaddr, sizeof(servaddr));

	servaddr.sin6_family = AF_INET6;
	servaddr.sin6_port   = htons(13);	/* daytime server */
    //< 将IP地址转换为网络地址
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
		UNIX_NET_DEBUG("inet_pton error for %s", argv[1]);

    //< notice kernel the sockfd and sevaddr info 
	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		UNIX_NET_DEBUG("connect error");

    //< this will block util get the data
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			UNIX_NET_DEBUG("fputs error");
	}
	if (n < 0)
		UNIX_NET_DEBUG("read error");

	return 0;
}