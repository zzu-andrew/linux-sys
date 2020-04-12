#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>



/*
       ┌─────────────────────────┬───────────────┬─────────┐
       │Interface                │ Attribute     │ Value   │
       ├─────────────────────────┼───────────────┼─────────┤
       │acos(), acosf(), acosl() │ Thread safety │ MT-Safe │
       └─────────────────────────┴───────────────┴─────────┘
*/

int main(int argc, char const *argv[])
{
    
    double real = acos(-0.5);

    printf("%lf\n", real);
    return 0;
}
