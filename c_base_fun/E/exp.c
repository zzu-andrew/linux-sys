#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>



int main(int argc, char const *argv[])
{
    /* code */
    int i = 0;
    double ex = 0.0;
    for(i = 0; i < 10;i ++)
    {
        ex = exp(i);
        printf("ex[%d] = [%lf]\n",i, ex);
    }
    
    return 0;
}
