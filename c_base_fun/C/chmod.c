#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>

//chdir 改变当前目录的函数
int main(int argc, char const *argv[])
{
    /* 查看当前目录 */
    system("touch test");
    chmod("./test", S_IRUSR | S_IWUSR);
    system("ls -l ./test");
   
    return 0;
}
