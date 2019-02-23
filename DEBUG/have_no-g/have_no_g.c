//##########################################

//##########################################
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int v1 = 1;
float v2 = 0.01;

void func(int a, long b, short c, char d, long long e, float f, 
        double g, int *h,float *i, char *j)
{
    printf("a:%d, b:%ld,c:%d, d:%c,e:%lld\n"
           "f:%.3e, g: %.3e\nh: %p, i:%p, j%p\n", a, b, c, d, e, f, g, h, i, j);
}


int main(int argc, char * argv[])
{

    func(100, 35000L, 5, 'A', 123456789LL, 3.14, 2.99792458e8, 
            &v1, &v2, "string");
    return EXIT_SUCCESS;

}





