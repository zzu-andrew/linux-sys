#include <stdio.h>
#include "sys_tem.h"
#include "weak_func_test.h"
#include "func_test.h"




int main(int argc, char *argv[])
{   
    int ret = OK;

    ret |= test_func();
    


    if (ret != OK)
    {
        UNIX_DEBUG("some test is failed.\n\n");
    }
    
    return 0;
}
