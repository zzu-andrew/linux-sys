#ifndef __SYS_TEM_H__
#define __SYS_TEM_H__

#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>




/* 宏定义 */
#define EXIT_SUCCESS 0
#define EXIT_FAIL   -1

#define UNIX_SYS_DEBUG(...) do { \
                    printf("[%s], lien  = [%d]", __FILE__, __LINE__); \
                    printf(__VA_ARGS__); \
                     }while(0)


int inetBind(const char *service, int type, socklen_t *addrlen);

char *
inetAddressStr(const struct sockaddr *addr, socklen_t addrlen,
               char *addrStr, int addrStrLen);
int inetConnect(const char *host, const char *service, int type);

int
inetListen(const char *service, int backlog, socklen_t *addrlen);


#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))









#endif
