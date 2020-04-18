#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>

//chdir 改变当前目录的函数
int main(int argc, char const *argv[])
{
    int ret = 0;
    /* 查看当前目录 */
    system("pwd");
    ret = chdir("./..");
    if(ret == 0)
    {
        printf("chdir to .. success.\n");
    }
    else
    {
        printf("chdir to .. failed.\n");
    }
    
    system("pwd");
    return 0;
}
