[TOC]

## strace



- strace命令允许我们跟踪程序执行的系统调用，这个功能对于调试程序，或者只是简单的查看程序正在做些什么都是非常的有帮助的，strace最简单的用法如下：

```bash
$strace command arg ...
```

- 该命令会以给定的参数运行该命令，产生程序所执行的系统调用跟踪。默认情况下，strace会将产生的输出写入到stderr中，但我们可以通过 -o filename的选项来修改这个行为。
- 以下是输出的简单示例;

```c
andrew@andrew-Thurley:/work/linux_unix/sys_man/time$ strace ./show_time
execve("./show_time", ["./show_time"], [/* 67 vars */]) = 0
brk(NULL)                               = 0xd32000
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
open("/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=147804, ...}) = 0
mmap(NULL, 147804, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fddee415000
close(3)                                = 0
access("/etc/ld.so.nohwcap", F_OK)      = -1 ENOENT (No such file or directory)
open("/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\t\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1868984, ...}) = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fddee414000
mmap(NULL, 3971488, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7fddede4b000
mprotect(0x7fddee00b000, 2097152, PROT_NONE) = 0
mmap(0x7fddee20b000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1c0000) = 0x7fddee20b000
mmap(0x7fddee211000, 14752, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fddee211000
close(3)                                = 0
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fddee413000
mmap(NULL, 4096, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fddee412000
arch_prctl(ARCH_SET_FS, 0x7fddee413700) = 0
mprotect(0x7fddee20b000, 16384, PROT_READ) = 0
mprotect(0x601000, 4096, PROT_READ)     = 0
mprotect(0x7fddee43a000, 4096, PROT_READ) = 0
munmap(0x7fddee415000, 147804)          = 0
brk(NULL)                               = 0xd32000
brk(0xd53000)                           = 0xd53000
open("/usr/lib/locale/locale-archive", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=4763056, ...}) = 0
mmap(NULL, 4763056, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7fdded9c0000
close(3)                                = 0
open("/etc/localtime", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=554, ...}) = 0
fstat(3, {st_mode=S_IFREG|0644, st_size=554, ...}) = 0
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\3\0\0\0\3\0\0\0\0"..., 4096) = 554
lseek(3, -339, SEEK_CUR)                = 215
read(3, "TZif2\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\3\0\0\0\3\0\0\0\0"..., 4096) = 339
close(3)                                = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(136, 19), ...}) = 0
write(1, "ctime() of time() value is:  Wed"..., 54ctime() of time() value is:  Wed May 29 22:50:58 2019
) = 54
stat("/etc/localtime", {st_mode=S_IFREG|0644, st_size=554, ...}) = 0
write(1, "asctime() of local time is:  Wed"..., 54asctime() of local time is:  Wed May 29 22:50:58 2019
) = 54
write(1, "strftime() of local time is: \346\230\237"..., 69strftime() of local time is: 星期三, 29 五月 2019, 22:50:58 CST
) = 69
exit_group(0)                           = ?
+++ exited with 0 +++

```



程序源码如下：

```c
#include <time.h>
#include <locale.h>
#include "tlpi_hdr.h"

#define BUF_SIZE 200

int
main(int argc, char *argv[])
{
    time_t t;
    struct tm *loc;
    char buf[BUF_SIZE];

    if (setlocale(LC_ALL, "") == NULL)
        errExit("setlocale");   /* Use locale settings in conversions */

    t = time(NULL);

    printf("ctime() of time() value is:  %s", ctime(&t));

    loc = localtime(&t);
    if (loc == NULL)
        errExit("localtime");

    printf("asctime() of local time is:  %s", asctime(loc));

    if (strftime(buf, BUF_SIZE, "%A, %d %B %Y, %H:%M:%S %Z", loc) == 0)
        fatal("strftime returned 0");
    printf("strftime() of local time is: %s\n", buf);

    exit(EXIT_SUCCESS);
}
```

- 针对上面的输出，每个系统调用都是以一个函数的形式显示出来的，输入和输出参数都在括号中给出，从以上实例来看，参数是以符号的形式打印出来的。
- 位掩码以相应的符号常量形式来代表
- 字符串以文本的形式打印出来(长度上限是32个字符，但是 -s strsize可以更改这个上限)
- 结构体字段是单独显示的(默认情况下，只有大型结构体的子集缩写才会被显示出来，但是-v选项可以显示整个结构体)

在被跟踪调用的有括号后，strace打印出一个等于号(=)，紧跟着的是该系统调用，的返回值，如果系统调用失败了，也会显示处errno错误码的符号标示，因此在上面的access()调用中，我们看到对应的错误码ENOENT被打印了出来。

- 就算是一个简单的程序strace打印也会很长，因此常用一下方法来提取自己感兴趣的信息

1. **grep**过滤strace的输出

```bash
strace date 2>$1 | grep open
```

2. 使用 -e 选项来选择要跟踪的实践，比如，我们可以使用如下命令

```bash
strace -e trace=open,close date
```

​	需要注意的是系统调用的真是名称同它对应的glibc包装函数是有区别的，strace跟踪的是系统调用，上述两种方法中给出的过滤条件也得是系统调用的函数名，这些可以在glibc中查找，看看包装函数中做了那些转换。

​	具体的在安装strace之后使用man strace查看















==欢迎关注公众号==

![](./../picture/weixin.jpg)