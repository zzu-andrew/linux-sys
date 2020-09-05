#include <stdio.h>


int echo_demo(void);

int main(int argc, char const *argv[])
{
    int ret = 0;
    ret = echo_demo();
    if(ret != 0)
    {
        printf("call echo demo failed\n");
    }

    return 0;
}
