## A开头的`Linux C`函数



## `abort`

异常终止程序

`abort`函数在调用的时候，会触发`SIGABRT`信号

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void signalHandler(int sig);

// 信号处理函数
void signalHandler(int sig)
{
  if(sig == SIGABRT)    //对应ctrl+c
  {
    printf("abort 函数被调用，触发SIGABRT信号量 。\n");
  }
}
//以下是主函数
int main(int argc,char *argv[])
{
  signal(SIGABRT, signalHandler);   //注册SIGINT对应的处理函数

  abort();
 
  printf("程序走不到这里。\n");
  return 0;
}

```



## `abs`

对整数求绝对值的函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
/*
    ┌──────────────────────────────┬───────────────┬─────────┐
    │Interface                     │ Attribute     │ Value   │
    ├──────────────────────────────┼───────────────┼─────────┤
    │abs(), labs(), llabs(), imax‐ │ Thread safety │ MT-Safe │
    │abs()                         │               │         │
    └──────────────────────────────┴───────────────┴─────────┘
*/
int main(int argc, char const *argv[])
{
    /* code */
    
    printf("abs(-1) = [%d]\n", abs(-1));
    return 0;
}

```





## `acos`

反余弦函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>



/*
       ┌─────────────────────────┬───────────────┬─────────┐
       │Interface                │ Attribute     │ Value   │
       ├─────────────────────────┼───────────────┼─────────┤
       │acos(), acosf(), acosl() │ Thread safety │ MT-Safe │
       └─────────────────────────┴───────────────┴─────────┘
*/

int main(int argc, char const *argv[])
{
    
    double real = acos(-0.5);

    printf("%lf\n", real);
    return 0;
}

```



## `asctime time localtime`

系统时间获取函数，注意这几个函数的时间受校时函数的影响

`time() returns the time as the number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC)`

`loacaltime() 将time_t 结构的数据，转换为对应的日历时间，详见tm结构体`

`asctime() 将日历形式结构体时间数据转换为对应的字符串`

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <string.h>

#if 0
struct tm
{
  int tm_sec;			/* Seconds.	[0-60] (1 leap second) */
  int tm_min;			/* Minutes.	[0-59] */
  int tm_hour;			/* Hours.	[0-23] */
  int tm_mday;			/* Day.		[1-31] */
  int tm_mon;			/* Month.	[0-11] */
  int tm_year;			/* Year	- 1900.  */
  int tm_wday;			/* Day of week.	[0-6] */
  int tm_yday;			/* Days in year.[0-365]	*/
  int tm_isdst;			/* DST.		[-1/0/1]*/


  long int __tm_gmtoff;		
  const char *__tm_zone;	
};
#endif


int main(int argc, char const *argv[])
{
    //定义时间结构体指针,结构体值见注释
    struct tm *pTm = NULL;
    time_t nowTime;
    char *pSzAscTime = NULL;

    memset(&nowTime, 0 , sizeof(nowTime));

    nowTime = time(NULL);
    pTm = localtime(&nowTime);

    pSzAscTime = asctime(pTm);

    printf("Asc time = %s", pSzAscTime);

    return 0;
}

```

## `asin`

反正弦函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
 

int main(int argc, char const *argv[])
{
    
    double real = asin(-0.5);

    printf("%lf\n", real);
    return 0;
}

```



## `assert`

`assert()函数是诊断函数，诊断一个表达式是否为真，只有为真才能继续执行`

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <assert.h>

/**
 * 诊断表达式的真值
 * */

int main(int argc, char const *argv[])
{
    
    assert(1);
    return 0;
}

```



## `atan`

`atan() 反正弦函数`

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    
    double real = atan(-0.5);

    printf("%lf\n", real);
    return 0;
}

```



## `atexit`

`atexit() 在程序要退出时注册要调用的函数`

该函数在做项目，一个进程中有多个线程，又申请内存需要释放的时候，非常有用，将需要释放的内存放到被注册的函数里面，无论在那个线程里面退出程序，都会出发释放资源的函数，这样就不用担心资源的释放问题了。

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

// C语言中用于注册  正常退出时调用的函数
// 当程序调用exit函数进行推出时就会先调用atexit函数注册的函数
#define	TRUE		1			//真 
#define	FALSE		0			//假
#define YES			1			//是
#define NO          0			//否 
#define	OK			0			//通过
#define	ERROR		-1			//错误

void callHnadler(void);

void callHnadler(void)
{
    printf("这个函数会在函数退出前调用一次\n");
}

int main(int argc, char const *argv[])
{
    int ret = ERROR;   
    ret = atexit(callHnadler);
    if(OK != ret)
    {
        printf("atexit register callHandler function failed\n");
    }

    return 0;
}
```

## `atof`

将字符串转换为浮点数的函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

// 将字符串转换为浮点数的函数

int main(int argc, char const *argv[])
{
    
    printf("0.12345 = [%f]\n", atof("0.12345"));
    return 0;
}
```



## `atoi`

将字符串转换为整数的函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

// 将字符串转化为整数的函数

int main(int argc, char const *argv[])
{
    
    printf("12345 = [%d]\n", atoi("12345"));
    return 0;
}
```



## `atol`

将字符串转换为长整型的函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>

// 将字符串转化为整数的函数

int main(int argc, char const *argv[])
{
    
    printf("12345 = [%d]\n", atol("12345"));
    return 0;
}
```









