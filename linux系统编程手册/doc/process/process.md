## 进程



#### getpid函数

```c
#include <sys/types.h>
#include <unistd.h>

pid_t getpid(void);
```

- getpid()系统调用返回调用进程的进程号，返回的类型为 pid_t专门用于存储进程号

#### getppid()函数

```c
#include <sys/types.h>
#include <unistd.h>

pid_t getppid(void);
```

- getppid()函数用于获取父进程的进程号，**孤儿进程**进程号是1(init进程的进程号)

> 每个进程的内存由很多部分组成，通常称之为"段`segment`"

1. 文本段包含了运行的程序及其语言指令
2. 初始化数据段包含显示初始化的全局变量和静态变量
3. 未初始化段，包含了未进行显示初始化的全局变量和静态变量
4. 栈(stack)是一个动态增长和收缩的段，由栈帧组成
5. 堆(heap)是可在运行时(为变量)动态进行内存分配的一块区域

```c
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];            //<  未初始化段
int primes[] = { 2, 3, 5, 7 };  //< 初始化数据段

static int
square(int x)                   //< 栈帧
{
    int result;                 //< 为squre 申请栈  存储result变量

    result = x * x;
    return result;              //< 通过寄存器，返回对应的值
}

static void
doCalc(int val)                 //< 存在栈中
{
    printf("The square of %d is %d\n", val, square(val));

    if (val < 1000) {
        int t;                 

        t = val * val * val;
        printf("The cube of %d is %d\n", val, t);
    }
}

int
main(int argc, char *argv[])    //< 存在栈中
{
    static int key = 9973;      //< 初始化数据段
    static char mbuf[10240000]; //< 为初始化数据段
    char *p;                    

    p = malloc(1024);           //< 在堆中申请内存

    doCalc(key);

    exit(EXIT_SUCCESS);
}

```



### 虚拟内存

**空间局限性**:程序倾向于访问在最近访问过的内存地址附近的内存(由于指令是顺序执行的，且有时会按照顺序处理数据结构)

**时间局限性**：指程序倾向于在不久的将来再次访问最近刚访问过的内存地址

正式由于访问的局部特性，使得程序即便仅有部分地址空间存在与RAM中，依然可能得以执行

程序编译之后执行，会将主函数从命令行中得到的字符串打印出来

```c

#include <stdio.h>

int
main(int argc, char *argv[])
{
    int j;

    for (j = 0; j < argc; j++)
        printf("argv[%d] = %s\n", j, argv[j]);

    return 0;
}

```

执行结果

```bash
$ ./a.out aa dd gg hh hh 
argv[0] = ./a.out
argv[1] = aa
argv[2] = dd
argv[3] = gg
argv[4] = hh
argv[5] = hh
```

### 显示进程环境

**编写程序，显示出环境变量**

```c
#include <stdio.h>

//< 存储环境变量的的指针
extern char **environ;
                /* Or define _GNU_SOURCE to get it from <unistd.h> */

int
main(int argc, char *argv[])
{
    char **ep;

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    return 0;
}
```





















