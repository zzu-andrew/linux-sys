#include <stdio.h>


int echo_demo(void);
void src1(void);

int main(int argc, char const *argv[])
{
    int ret = 0;
    ret = echo_demo();
    if(ret != 0)
    {
        printf("call echo demo failed\n");
    }

    src1();
    return 0;
}
