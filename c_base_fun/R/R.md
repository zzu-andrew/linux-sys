#

# R开头的函数



读取文件内容函数

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

重新分配内存函数

```c
 #include <stdlib.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
```

删除一个文件的函数

```c
#include <stdio.h>

int remove(const char *pathname);
```



更改文件名函数

```c
#include <stdio.h>

int rename(const char *oldpath, const char *newpath);

#include <fcntl.h>           /* Definition of AT_* constants */
#include <stdio.h>

int renameat(int olddirfd, const char *oldpath,
             int newdirfd, const char *newpath);

int renameat2(int olddirfd, const char *oldpath,
              int newdirfd, const char *newpath, unsigned int flags);
```

回到文件开头函数

```c
 #include <stdio.h>

int fseek(FILE *stream, long offset, int whence);

long ftell(FILE *stream);

void rewind(FILE *stream);

int fgetpos(FILE *stream, fpos_t *pos);
int fsetpos(FILE *stream, const fpos_t *pos);
```

删除文件夹函数

```c
 #include <unistd.h>

int rmdir(const char *pathname);
```





