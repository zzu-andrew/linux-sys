[TOC]

# 深入文件IO

[git仓库]:<https://github.com/zzu-andrew/linux-sys>

![img](./../../doc/picture/gitchat.svg)

## fcntl函数

- 成功返回值根据cmd的值确定，失败返回 -1

```c
SYNOPSIS
       #include <unistd.h>
       #include <fcntl.h>

       int fcntl(int fd, int cmd, ... /* arg */ );

```

## dup函数

- dup函数用于复制一个打开的文件描述符，oldfd，并返回一个新的文件描述符，二者指向同一打开的文件句柄
- dup2系统调用会为oldfd参数所指定的文件描述符创建副本，其编号由newfd参数指定，如果由newfd指定的文件描述符之前已经打开，那么dup2会首先将其关闭，

```c       #include <unistd.h>

       int dup(int oldfd);
       int dup2(int oldfd, int newfd);
```

## pread 和 pwrite

- 系统调用，pread()和pwrite()，完成与read()和write()相类似的工作，只是前两者会在offset参数所指定的位置进行I/O操作，而非始于文件的当前偏移量处，而且它们不会改变文件的当前的偏移量

```c       #include <unistd.h>

       ssize_t pread(int fd, void *buf, size_t count, off_t offset);

       ssize_t pwrite(int fd, const void *buf, size_t count, off_t offset);
```



## 分散式和集中输出

**readv()和writev()**

```c       #include <sys/uio.h>

       ssize_t readv(int fd, const struct iovec *iov, int iovcnt);

       ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

       ssize_t preadv(int fd, const struct iovec *iov, int iovcnt,
                      off_t offset);

       ssize_t pwritev(int fd, const struct iovec *iov, int iovcnt,
                       off_t offset);
```



程序示例

```c
#include "sys_tem.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    struct iovec iov[3];
    struct stat myStruct;       /* First buffer */
    int x;                      /* Second buffer */
    char temp[60];
#define STR_SIZE 100
    char str[STR_SIZE];         /* Third buffer */
    ssize_t numRead, totRequired;

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
    {
        sprintf(temp, "%s file", argv[0]);
        perror(temp);
    }
        

    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        perror("open");

    totRequired = 0;

    iov[0].iov_base = &myStruct;
    iov[0].iov_len = sizeof(struct stat);
    totRequired += iov[0].iov_len;

    iov[1].iov_base = &x;
    iov[1].iov_len = sizeof(x);
    totRequired += iov[1].iov_len;

    iov[2].iov_base = str;
    iov[2].iov_len = STR_SIZE;
    totRequired += iov[2].iov_len;

    numRead = readv(fd, iov, 3);
    if (numRead == -1)
        perror("readv");

    if (numRead < totRequired)
        printf("Read fewer bytes than requested\n");

    printf("total bytes requested: %ld; bytes read: %ld\n",
            (long) totRequired, (long) numRead);
    exit(EXIT_SUCCESS);
}

```







































![码上嵌入式](./../../doc/picture/weixin.jpg)









