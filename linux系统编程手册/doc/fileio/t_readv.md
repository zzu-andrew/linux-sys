[TOC]

# 深入文件IO

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











































![码上嵌入式](./../../doc/picture/weixin.jpg)









