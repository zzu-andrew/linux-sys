#

# P开头的函数



显示错误的函数

```c
 #include <stdio.h>

void perror(const char *s);

#include <errno.h>
const char * const sys_errlist[];
int sys_nerr;
int errno;       /* Not really declared this way; see errno(3) */
```



流输出函数家族

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

 #include <stdio.h>

int fputc(int c, FILE *stream);

int fputs(const char *s, FILE *stream);

int putc(int c, FILE *stream);

int putchar(int c);

int puts(const char *s);
```

将字符串放入当前环境的函数

```c
 #include <stdlib.h>

int putenv(char *string);
The  putenv()  function adds or changes the value of environment variables.  The argument string is of the
       form name=value.  If name does not already exist in the environment, then string is added to the  environ‐
       ment.   If  name  does  exist,  then the value of name in the environment is changed to value.  The string
       pointed to by string becomes part of the environment, so altering the string changes the environment.
```





