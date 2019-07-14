#include <stdio.h>

//< 存储环境变量的的指针
extern char **environ;
                /* Or define _GNU_SOURCE to get it from <unistd.h> */

int
main(int argc, char *argv[])
{
    char **ep;

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);

    return 0;
}