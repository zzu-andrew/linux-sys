#

# W开头的函数

将宽字符串转换成多字节字符串

```c
#include <stdlib.h>
size_t wcstombs(char *dest, const wchar_t *src, size_t n);
#include <stdlib.h>
int wctomb(char *s, wchar_t wc);
```

写文件函数

```c
#include <unistd.h>
ssize_t write(int fd, const void *buf, size_t count);
```

