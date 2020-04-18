#

# S开头的函数



格式化输入函数

```c
 #include <stdio.h>

int scanf(const char *format, ...);
int fscanf(FILE *stream, const char *format, ...);
// 格式串读取函数
int sscanf(const char *str, const char *format, ...);

#include <stdarg.h>

int vscanf(const char *format, va_list ap);
int vsscanf(const char *str, const char *format, va_list ap);
int vfscanf(FILE *stream, const char *format, va_list ap);
```

设置缓冲区大小函数，详细使用在Linux系统编程中进行说明

```c
 #include <stdio.h>

void setbuf(FILE *stream, char *buf);

void setbuffer(FILE *stream, char *buf, size_t size);

void setlinebuf(FILE *stream);

int setvbuf(FILE *stream, char *buf, int mode, size_t size);
```

安装信号处理函数

```c
 #include <signal.h>

typedef void (*sighandler_t)(int);

sighandler_t signal(int signum, sighandler_t handler);
```

格式化输出到数组函数

```c
 #include <stdio.h>

int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);
int dprintf(int fd, const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

#include <stdarg.h>

int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```

平方根

```c
 #include <math.h>

double sqrt(double x);
float sqrtf(float x);
long double sqrtl(long double x);

Link with -lm.
```

启动伪随机数

```c
 #include <stdlib.h>

int rand(void);

int rand_r(unsigned int *seedp);

void srand(unsigned int seed);
```



字符串比较函数

```c
 #include <string.h>

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);
```

字符串复制函数

```c
 #include <string.h>

char *strcpy(char *dest, const char *src);

char *strncpy(char *dest, const char *src, size_t n);
```

将错误号转换为字符串函数

```c
 #include <string.h>

char *strerror(int errnum);

int strerror_r(int errnum, char *buf, size_t buflen);
/* XSI-compliant */

char *strerror_r(int errnum, char *buf, size_t buflen);
/* GNU-specific */

char *strerror_l(int errnum, locale_t locale);
```

求字符串长度

```c
 #include <string.h>

size_t strlen(const char *s);
```

字符串连接函数

```c
 #include <string.h>

char *strcat(char *dest, const char *src);

char *strncat(char *dest, const char *src, size_t n);
```

字符串比较函数

```c
 #include <string.h>

int strcmp(const char *s1, const char *s2);

int strncmp(const char *s1, const char *s2, size_t n);
```

字符串搜索函数

```c
 #include <string.h>
// 正向搜索字符串中的字符
char *strchr(const char *s, int c);
// 反向搜索字符串中的字符
char *strrchr(const char *s, int c);
 #include <string.h>
// 字符串中搜索指定的字符串
char *strstr(const char *haystack, const char *needle);

#define _GNU_SOURCE         /* See feature_test_macros(7) */

#include <string.h>
// 字符串中搜索指定的字符串 或略大小写差异
char *strcasestr(const char *haystack, const char *needle);

```

搜索字符串标记

```c
 #include <string.h>

char *strtok(char *str, const char *delim);

char *strtok_r(char *str, const char *delim, char **saveptr);
```

执行操作系统命令

```c
#include <stdlib.h>

int system(const char *command);
```

