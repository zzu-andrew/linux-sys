[TOC]

## 文件描述符

​	所有的I/O操作的系统调用都以文件描述符，一个非负整数(通常是小整数)，来指代打开的文件。

- open函数打开pathname所标识的文件，并返回文件描述文件描述符

```c  #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

       int open(const char *pathname, int flags);
       int open(const char *pathname, int flags, mode_t mode);

       int creat(const char *pathname, mode_t mode);

       int openat(int dirfd, const char *pathname, int flags);
       int openat(int dirfd, const char *pathname, int flags, mode_t mode);
```

- read函数，调用从fd所指代的打开的文件中，读取至多count字节的数据，并保存到buf中去

```c
 #include <unistd.h>
 ssize_t read(int fd, void *buf, size_t count);

```

- write函数，调用从buf中读取多达count字节数，将数据写入到fd指代的已打开的文件中

```c
       #include <unistd.h>

       ssize_t write(int fd, const void *buf, size_t count);
```

- close函数， 关闭已打开的文件描述符 fd

```c
       #include <unistd.h>

       int close(int fd);
```





```c
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef BUF_SIZE        /* Allow "cc -D" to override definition */
#define BUF_SIZE 1024
#endif


int main(int argc, char *argv[])
{
    int inputFd, outputFd, openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if (argc != 3 || strcmp(argv[1], "--help") == 0)
        printf("%s old-file new-file\n", argv[0]);

    /* Open input and output files */

    inputFd = open(argv[1], O_RDONLY);
    if (inputFd == -1)
        printf("opening file %s", argv[1]);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH;      /* rw-rw-rw- */
    outputFd = open(argv[2], openFlags, filePerms);
    if (outputFd == -1)
        printf("opening file %s", argv[2]);

    /* Transfer data until we encounter end of input or an error */

    while ((numRead = read(inputFd, buf, BUF_SIZE)) > 0)
        if (write(outputFd, buf, numRead) != numRead)
            printf("couldn't write whole buffer");
    if (numRead == -1)
        printf("read");

    if (close(inputFd) == -1)
        printf("close input");
    if (close(outputFd) == -1)
        printf("close output");

    exit(EXIT_SUCCESS);
}

```



![码上嵌入式](./../../doc/picture/weixin.jpg)