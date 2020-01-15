#ifndef __UNIX_NET_PUBLIC__
#define __UNIX_NET_PUBLIC__
#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <time.h>


#define UNIX_NET_DEBUG(...) do { \
                    printf("[%s], line = [%d]", __FILE__, __LINE__); \
                    printf(__VA_ARGS__); \
                     }while(0)
  

#define MAXLINE 4096

#define LISTENQ 1024



#endif   //< __UNIX_NET_PUBLIC__



