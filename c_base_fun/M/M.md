# G开头的函数

> 文件操作相关的函数都放到`linux`系统编程中进行更新

```c
#include <stdlib.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

内存分配与释放函数函数
    malloc()  申请指令大小的内存，并返回指向内存的指针。申请失败返回NULL.
    free() 释放申请的内存
    calloc()  批量内存申请，申请个数为nmemb，大小为size的内存
   realloc() 改变ptr指针指向内存的大小
```



```c
 #include <sys/stat.h>
#include <sys/types.h>

int mkdir(const char *pathname, mode_t mode);

mkdir创建目录文件，mode指定目录文件的权限
```

 搜索内存块中的字符

```c
 #include <string.h>

       void *memchr(const void *s, int c, size_t n);

       void *memrchr(const void *s, int c, size_t n);

       void *rawmemchr(const void *s, int c);
```

 比较内存块

```c
 #include <string.h>
int memcmp(const void *s1, const void *s2, size_t n);
```

复制内存块

```c
#include <string.h>

void *memcpy(void *dest, const void *src, size_t n);

 #include <string.h>

  void *memmove(void *dest, const void *src, size_t n);
memmove用于拷贝字节，如果目标区域和源区域有重叠的话，memmove能够保证源串在被覆盖之前将重叠区域的字节拷贝到目标区域中，但复制后源内容会被更改。但是当目标区域与源区域没有重叠则和memcpy函数功能相同。
```

初始化内存

```c
 #include <string.h>
void *memset(void *s, int c, size_t n);
```

建立一个唯一的文件名函数

```c
 #include <stdlib.h>

 char *mktemp(char *template);
```

 分解为小数和小数部分

```c

 #include <math.h>

double modf(double x, double *iptr);
float modff(float x, float *iptr);
long double modfl(long double x, long double *iptr);

Link with -lm.
    
     These  functions  break  the argument x into an integral part and a fractional part, each of which has the
       same sign as x.  The integral part is stored in the location pointed to by iptr.
```









