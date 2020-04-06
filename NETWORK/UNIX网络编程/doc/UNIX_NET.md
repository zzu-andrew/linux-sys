[TOC]

![](./../picture/svg/linux.svg)![](./../picture/svg/markdown.svg)

# UNIX_NET

## 获取服务器时间

### connect函数

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
int connect(int sockfd, const struct sockaddr *addr,
            socklen_t addrlen);

DESCRIPTION
       The  connect()  system  call connects the socket referred to by the file descriptor sockfd to the address specified by addr.  The addrlen argument specifies the size of addr.  The format  of  the address  in  addr is determined by the address space of the socket sockfd; see socket(2) for fur‐
       ther details.

    If the socket sockfd is of type SOCK_DGRAM, then addr is the address to which datagrams are  sent by  default,  and  the  only address from which datagrams are received.  If the socket is of type SOCK_STREAM or SOCK_SEQPACKET, this call attempts to make a connection  to  the  socket  that  is bound to the address specified by addr.

    Generally, connection-based protocol sockets may successfully connect() only once; connectionless protocol sockets may use connect() multiple times to change  their  association.   Connectionless sockets  may  dissolve  the  association by connecting to an address with the sa_family member of sockaddr set to AF_UNSPEC (supported on Linux since kernel 2.2).
    
RETURN VALUE
       If the connection or binding succeeds, zero is returned.  On error, -1 is returned, and errno  is set appropriately.

```



### 获取时间客户端程序实现

```c
#include "unix_net_public.h"
#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#define MAXLINE 4096


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
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) <  0)
    {
        perror("socket error!\n");
    }

    //<  将地址结构体中的数据进行清空处理
    bzero(&servaddr, sizeof(servaddr));
    
    //< 构造结构体
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(8560); // 没有找到时间服务器使用ssh端口连接自己的电脑测试连 connect函数的实现


    //< 将点十进制地址转换为网络地址
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
    {
        perror("inet_pton error  \n");
    }

    //< 使用connect创建连接
    UNIX_NET_DEBUG("connect start\n");
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

```

**支持IPv6的实现**

```c
#include "unix_net_public.h"


int
main(int argc, char **argv)
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
	servaddr.sin6_port   = htons(8560);	/* daytime server */
    //< 将IP地址转换为网络地址
	if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
		UNIX_NET_DEBUG("inet_pton error for %s", argv[1]);

	if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0)
		UNIX_NET_DEBUG("connect error");

    //< 使用阻塞的凡是进行read函数读取数据
	while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
		recvline[n] = 0;	/* null terminate */
		if (fputs(recvline, stdout) == EOF)
			UNIX_NET_DEBUG("fputs error");
	}
	if (n < 0)
		UNIX_NET_DEBUG("read error");

	return 0;
}

```



### 获取时间服务器实现

```c
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
    //< 尽量使用大于8000的端口，小端口在linux上使用可能会报错不让使用
	servaddr.sin_port        = htons(8560);	/* daytime server */

    //< 绑定套接字
	bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	listen(listenfd, LISTENQ);

	for ( ; ; ) {
		connfd = accept(listenfd, (struct sockaddr *) NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        write(connfd, buff, strlen(buff));

		close(connfd);
	}
}

```





**测试**

```c
$ ./putdaytimesrv &
[1] 2952
$ ./getdaytimetcpclient 127.0.0.1
[getdaytimetcpclient.c], lien  = [47]connect start
[getdaytimetcpclient.c], lien  = [52]connect is end !
Sun Jul 14 14:57:22 2019
```



数据发送的过程刚好是三次握手，四次挥手加上一次(PSH,ACK)

----

### 一些声明

netstat -i 提供网络接口的信息，我们还指定-n 标志以输出数值地址，而不是试图将它们反向解析成名字

其中环回(loopback)接口称为lo，以太网接口称为eth0。

netstat -r 展示路由表相当于 route -n 

```bash
andrew@andrew-Thurley:/work/linux-sys/NETWORK/UNIX网络编程$ route -n
内核 IP 路由表
目标            网关            子网掩码        标志  跃点   引用  使用 接口
0.0.0.0         192.168.0.1     0.0.0.0         UG    600    0        0 wlp3s0b1
169.254.0.0     0.0.0.0         255.255.0.0     U     1000   0        0 wlp3s0b1
192.168.0.0     0.0.0.0         255.255.255.0   U     600    0        0 wlp3s0b1
andrew@andrew-Thurley:/work/linux-sys/NETWORK/UNIX网络编程$ netstat -r
内核 IP 路由表
Destination     Gateway         Genmask         Flags   MSS Window  irtt Iface
default         192.168.0.1     0.0.0.0         UG        0 0          0 wlp3s0b1
link-local      *               255.255.0.0     U         0 0          0 wlp3s0b1
192.168.0.0     *               255.255.255.0   U         0 0          0 wlp3s0b1

```

使用ifconfig 可以获取各个网络接口的详细信息 

**找出本地网络众中众多主机的方法**

在ifconfig之后

```bash
andrew@andrew-Thurley:/work/linux-sys/NETWORK/UNIX网络编程$ ifconfig
enp4s0    Link encap:以太网  硬件地址 xxxxxxxxxxxxxxxxxx  
          UP BROADCAST MULTICAST  MTU:1500  跃点数:1
          接收数据包:0 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:0 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:1000 
          接收字节:0 (0.0 B)  发送字节:0 (0.0 B)

lo        Link encap:本地环回  
          inet 地址:127.0.0.1  掩码:255.0.0.0
          inet6 地址: ::1/128 Scope:Host
          UP LOOPBACK RUNNING  MTU:65536  跃点数:1
          接收数据包:77460 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:77460 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:1000 
          接收字节:6116834 (6.1 MB)  发送字节:6116834 (6.1 MB)

wlp3s0b1  Link encap:以太网  硬件地址 xxxxxxxxxxxxxxxxxxxx  
          inet 地址:192.168.0.103  广播:192.168.0.255  掩码:255.255.255.0
          inet6 地址: xxxxxxxxxxxxxxxxxxxxxx Scope:Link
          UP BROADCAST RUNNING MULTICAST  MTU:1500  跃点数:1
          接收数据包:1071740 错误:0 丢弃:0 过载:0 帧数:0
          发送数据包:446685 错误:0 丢弃:0 过载:0 载波:0
          碰撞:0 发送队列长度:1000 
          接收字节:1504629481 (1.5 GB)  发送字节:55271250 (55.2 MB)

```

通过ping 广播地址可以得到

```bash
$ ping -b 192.168.0.255
WARNING: pinging broadcast address
PING 192.168.0.255 (192.168.0.255) 56(84) bytes of data.
64 bytes from 192.168.0.1: icmp_seq=1 ttl=64 time=3.49 ms

```

通过ping -b + 广播地址，可以回复ping的设备都会对设备进行回复，这样就能找到同一局域网下面的主机的个数以及IP

当然找到了之后可以使用nmap进行扫描发现主机开放的端口，使用cain破解一些加密信息(仅用于测试)

当64位系统出现时，数据占位大小的方面有以下变化：

| 数据类型 | ILP32模型 | Lp64模型 |
| -------- | --------- | -------- |
| char     | 8         | 8        |
| short    | 16        | 16       |
| int      | 32        | 32       |
| long     | 32        | 64       |
| 指针     | 32        | 64       |

在上述实现的获取时间的客户端和服务器中，客户端使用connect建立连接，完成三次握手，服务器使用accept完成三次握手

![[三次握手]([https://baike.baidu.com/item/%E4%B8%89%E6%AC%A1%E6%8F%A1%E6%89%8B/5111559?fr=aladdin](https://baike.baidu.com/item/三次握手/5111559?fr=aladdin))](./../picture/network/三次握手.jpg)



-----

## 基本的套接字编程

### 套接字的地址结构

> 大多数的套接字函数都需要一个指向套接字地址结构的指针作为参数，每个协议族都定义它自己的套接字地址结构。这些结构的名字均以sockaddr_开头，并以每个协议族的唯一的后缀结尾

1. socket函数指定套接字
2. connect函数建立与TCP服务器的连接
3. bind函数把一个本地地址协议地址赋予一个套接字
4. listen函数，仅TCP服务器调用，它完成两件事
   - 当socket创建一个套接字时，它被假设为一个主动套接字，也就是说它是一个将调用connect发起连接的客户端的套接字。listen函数把一个未连接的套接字转换成一个被动套接字，指示内核应接受指向该套接字的连接请求，根据TCP状态转换图，调用listen函数导致套接字从CLOSED状态转换为LISTEN状态
   - 本函数的第二个参数规定了内核应该为相应的套接字排队的最大连接数。

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int listen(int sockfd, int backlog);
backlog == 规定内核应该为相应的套接字排队的最大的连接数，这样就能防止连接数到达时，还有客户连接，并且客户端还在一直的等待

DESCRIPTION
       listen()  marks  the  socket referred to by sockfd as a passive socket, that is, as a socket that
       will be used to accept incoming connection requests using accept(2).

    The sockfd argument is a file descriptor that refers to a socket of type SOCK_STREAM or SOCK_SEQ‐
       PACKET.

    The  backlog  argument  defines  the maximum length to which the queue of pending connections for
        sockfd may grow.  If a connection request arrives when the queue is full, the client may  receive
       an  error  with an indication of ECONNREFUSED or, if the underlying protocol supports retransmis‐
       sion, the request may be ignored so that a later reattempt at connection succeeds.

```

5. accept函数是由TCP服务器调用，用于从已完成连接队列队头返回下一个已完成连接，如果已完成连接队列为空，那么进程被投入睡眠(假定套接字默认为阻塞方式)

   如果accept成功，呢么其返回的值即为由内核自动生成的一个全新的描述符，代表与所返回的客户的TCP连接。调用accept时，我们称它的第一个参数为监听套接字描述符，称它的返回值为已连接套接字描述符。一个服务器仅创建一个监听套接字，他在该服务器的声明周期内是一直存在的，内核为每一个由服务器进程接受的客户连接创建一个已连接套接字，当服务器完成对某个客户的服务时，相应的已连接套接字就被关闭

```c
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

**accept简单使用示例**

```c
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
    uint16_t client_port = 0; //< 对端口进行初始化，不初始化的值是不确定的

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

```

6.   getsockname和getpeername函数   ==== 117

   getsockname返回与某个套接字关联的本地协议地址

   getpeername返回与某个套接字关联的外地协议地址

7. close函数，UNIX close函数也用来关闭套接字

```c
#include <unistd.h>
int close(int fd)；
```

--------

## TCP客户-服务器程序示例

### 编写简单的回射服务器

- 客户从标准输入读取一行文本，并写会服务器
- 服务器从网络输入读入这行文本，并回射给客户
- 客户从网络输入读入这行回射文本，并显示在标准输出上

如图：

![](/work/linux-sys/NETWORK/out/UNIX网络编程/doc/UML/simple_uml/simple_tcp_srv_cli.svg)











## 高级枚举型定义实现

**C源文件**

```c
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
/*
实现原理说明：
首先在枚举型结构体中定义宏定义　#define ENUM_(name,num,size,desc)  MACRO_##name = num,
然后在引入头文件，头文件包含的宏定义的调用将在这里进行展开，展开之后，会得到一个由宏定义扩展之后的
枚举型结构体
*/
enum MACRO_ENUM
{
    #define ENUM_(name,num,size,desc)  MACRO_##name = num,
    #include "enum_example.h"
    MACRO_MAX,
};


int main(int argc, char *argv[])
{
    /* 经过宏扩展的之后的枚举型变量大小 */
    printf("after macro MACRO_MAX = [%d]\n", MACRO_MAX);

    return 0;
}

```

**`enum_example.h`**


```c

/**
 * @brief  宏定义实现枚举型的扩展
 * ＠　　　　该头文件仅用于扩展对应文件宏定义
 */

#define EXAM1_SIZE 1

ENUM_(EXAM1,EXAM1_SIZE,sizeof(int),"this is a enum example")

#define EXAM2_SIZE 2
ENUM_(EXAM2,EXAM1_SIZE,sizeof(int),"this is a enum example")

#define EXAM3_SIZE 30
ENUM_(EXAM3,EXAM3_SIZE,sizeof(int),"this is a enum example")

```



































------

## 小技巧

### 宏定义的使用&&变参函数的宏定义实现

```c
#define UNIX_NET_DEBUG(__VA_ARGS__...) do { \
                    printf("[%s], lien  = [%d]", __FILE__, __LINE__); \
                    printf(__VA_ARGS__); \
                     }while(0)
```





## 源码地址

[github]([https://github.com/zzu-andrew/linux-sys/tree/dfew/NETWORK/UNIX%E7%BD%91%E7%BB%9C%E7%BC%96%E7%A8%8B](https://github.com/zzu-andrew/linux-sys/tree/dfew/NETWORK/UNIX网络编程))

**关注公众号**

![扫码关注，持续更新](./../picture/weixin.jpg)

