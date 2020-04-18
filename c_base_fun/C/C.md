# C开头的函数



## `calloc`

内存分配函数

```c
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//void *calloc(size_t nmemb, size_t size);
// calloc  申请nmemb个大小为size的内存


struct student
{
    int age;
    char *name;
};

int main(int argc, char const *argv[])
{
    /* code */
    struct student *class1 = calloc(60, sizeof(struct student));



    free(class1);
    return 0;
}

```

## `ceil`

求不小于`num`的最小双精度整数