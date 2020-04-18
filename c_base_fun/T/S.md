#

# T开头的函数

计算弧度的正切值

```c
 #include <math.h>
 #include <math.h>

double tan(double x);
float tanf(float x);
long double tanl(long double x);

Link with -lm.
```

求当前时间的函数

```c
 #include <time.h>

time_t time(time_t *tloc);
```

产生临时文件名

```c
 #include <stdio.h>

char *tempnam(const char *dir, const char *pfx);
```



转换为小写字符函数

```c
 #include <ctype.h>

int toupper(int c);
int tolower(int c);

int toupper_l(int c, locale_t locale);
int tolower_l(int c, locale_t locale);
```

转换为大写字符函数

```c
 #include <ctype.h>

int toupper(int c);
int tolower(int c);

int toupper_l(int c, locale_t locale);
int tolower_l(int c, locale_t locale);
```

回退函数

```c
int ungetc(int c, FILE *stream);
```

用可变实际参数列表格式化写字符串

```c
 #include <stdarg.h>

int vprintf(const char *format, va_list ap);
int vfprintf(FILE *stream, const char *format, va_list ap);
int vdprintf(int fd, const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);
```




