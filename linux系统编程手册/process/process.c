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
