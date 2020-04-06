#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


enum MACRO_ENUM
{
    #define ENUM_(name,num,size,desc)  MACRO_##name = num,
    #include "enum_example.h"
    MACRO_MAX,
};


int main(int argc, char *argv[])
{
    /* 经过宏扩展的之后的枚举型变量大小 */
    printf("after macro MACRO_MAX = [%d]\n", MACRO_MAX);

    return 0;
}



