#include <math.h>
#include <float.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    double x, r;
    int exp;

    x = strtod(argv[1], NULL);
    r = frexp(x, &exp);

    printf("frexp(%g, &e) = %g: %g * %d^%d = %g\n",
            x, r, r, FLT_RADIX, exp, x);
   exit(EXIT_SUCCESS);
}