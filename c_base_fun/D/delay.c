#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>


void delay(int secon);

void delay(int secon)
{
    sleep(secon);
}

int main(int argc, char const *argv[])
{
    /* code */
    delay(6);
    return 0;
}
