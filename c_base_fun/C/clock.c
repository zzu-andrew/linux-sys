#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


//chdir 改变当前目录的函数
int main(int argc, char const *argv[])
{
    /* 查看当前目录 */
    long timeCount;
    int i = 0;
    for(i = 0; i < 12345; i++)
    {
        i++;
    }
    sleep(2);
    timeCount = clock();


    printf("timeCount = [%ld]\n", timeCount);
   
    return 0;
}
