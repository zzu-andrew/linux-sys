# G开头的函数

> 文件操作相关的函数都放到`linux`系统编程中进行更新

## `getcwd`

获取当前目录函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>


int main(int argc, char const *argv[])
{
    char pathName[128];
    char *pName = NULL;
    memset(pathName, 0, sizeof(pathName));
    
    pName = getcwd(pathName, sizeof(pathName));
    printf("pathName = [%s] pName = [%s]\n", pathName, pName);
    
    if(pathName == pName)
    {
        printf("pathName == pName\n");
    }
    return 0;
}

```

## `getenv`

获取指定的环境变量

```c
#include "c-base.h"



int main(int argc, char const *argv[])
{
    char szEnvName[2048] = "PATH";
    char *pEnvName = NULL;

    pEnvName = getenv(szEnvName);
    if(NULL != pEnvName)
    {
        printf("env = [%s]\n",
                 pEnvName);
    }
    return 0;
}
```


