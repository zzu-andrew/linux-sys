//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>
#include <stdlib.h>





int main(int argc, char * argv[])
{

    FILE *fp;
    fp = fopen("/etc/shadow", "r");
    if (fp == NULL)
    {
        printf("Error !\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}




