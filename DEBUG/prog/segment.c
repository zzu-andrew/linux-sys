//##########################################
//使用 dbg 调试段错误
//##########################################
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>

int main(int argc, char * argv[])
{
    void *p = NULL;
    while(1)
    {

       p = dlopen("./lib1.so", "RTLD_LAZY");

        if (p == NULL)
        {
            printf("Error !\n");
            return 1;
        }
        dlclose(p);
        sleep(100);
    }


    return EXIT_SUCCESS;

}




