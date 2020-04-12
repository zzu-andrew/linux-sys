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
