//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char * argv[])
{

    while(1)
    {

        FILE *fp;
        fp = fopen("/etc/shadow", "r");
        if (fp == NULL)
        {
            printf("Error !\n");
        }
        else
        {
            fclose(fp);
        }
        sleep(3);
    }


    return EXIT_SUCCESS;

}




