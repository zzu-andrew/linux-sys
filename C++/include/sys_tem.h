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
