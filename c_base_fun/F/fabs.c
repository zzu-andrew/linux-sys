#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>

//fabs 浮点数绝对值

int main(int argc, char const *argv[])
{
    /* code */
    double abs = 0.0;
    abs = fabs(-0.56);
    printf("abs = [%lf]\n", abs);
    
    return 0;
}
