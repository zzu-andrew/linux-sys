#include <stdio.h>
#include "sys_tem.h"
#include "weak_func_test.h"
#include "func_test.h"
#include "ds_extern.h"



int test_func(void)
{
    int ret = ERROR;
    ret = file_io_test();
    if (OK != ret)
    {
        UNIX_DEBUG("file_io_test is failed!\n");
    }
    
    ret = show_time();
    if (OK != ret)
    {
        UNIX_DEBUG("show_time is failed!\n");
    }

    ret = linear_list_test();
    if (OK != ret)
    {
        UNIX_DEBUG("linear_list_test is fialed!.\n");
    }

    return ret;
}



