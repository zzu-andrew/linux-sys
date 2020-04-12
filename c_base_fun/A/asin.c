#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
 

int main(int argc, char const *argv[])
{
    
    double real = asin(-0.5);

    printf("%lf\n", real);
    return 0;
}
