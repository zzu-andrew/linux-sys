#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

/*
    ┌──────────────────────────────┬───────────────┬─────────┐
    │Interface                     │ Attribute     │ Value   │
    ├──────────────────────────────┼───────────────┼─────────┤
    │abs(), labs(), llabs(), imax‐ │ Thread safety │ MT-Safe │
    │abs()                         │               │         │
    └──────────────────────────────┴───────────────┴─────────┘
*/



int main(int argc, char const *argv[])
{
    /* code */
    
    printf("abs(-1) = [%d]\n", abs(-1));
    return 0;
}
