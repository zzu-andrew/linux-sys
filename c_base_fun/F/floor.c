#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


// floor函数 用于求解 不大于x的双精度整数
//double floor(double x);

int main(int argc, char const *argv[])
{
    /* code */
    double x = -12.36458;
    double y = floor(x);
    printf("floor(%lf) = [%f]\n", x, y);

    return 0;
}
