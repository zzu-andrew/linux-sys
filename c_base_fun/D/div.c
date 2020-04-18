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
    div_t divRes;

    divRes = div(17, 5);

    printf("divRes.quot = [%d], divRes.rem = [%d]\n", divRes.quot, divRes.rem);
    return 0;
}
