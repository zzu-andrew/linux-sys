---
LSEEK
---

[TOC]

## lseek函数

- lseek函数，定位到打开文件的指定位置处

```c
       #include <sys/types.h>
       #include <unistd.h>

       off_t lseek(int fd, off_t offset, int whence);
```

- fd文件描述符
- offset偏移量
- whence在何处偏移

```c
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>


int main(int argc, char *argv[])
{

    off_t offset;
    int fd;
    ssize_t numWritten;


    fd = open(argv[1], O_RDWR | O_CREAT,
                S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP |
                S_IROTH | S_IWOTH);                     /* rw-rw-rw- */
    if (fd == -1)
        perror("open");

        
    offset = 10000;
    //< SEEK_SET说明是从文件头部开始偏移
    if (lseek(fd, offset, SEEK_SET) == -1)
            perror("lseek");
    printf("%s: seek succeeded\n", "10000");
    numWritten = write(fd, "abc", strlen("abc"));
    printf("write  = %ld\n", (long int)numWritten);

    if (close(fd) == -1)
        perror("close");

    exit(0);
}

```

- test

```bash
$ touch tfile
$ ./seek_io tfile 
10000: seek succeeded
write  = 3
$ ls -l tfile 
-rw-rw-r-- 1 andrew andrew 10003 5月  25 23:27 tfile
```

- ==说明==
- 打开文件之后，从文件开始处偏移10000之后有写入3个字符，所以为10003



![码上嵌入式](./../../doc/picture/weixin.jpg)