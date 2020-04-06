#include <stdio.h>
#include "weak_func_test.h"



 /**
  * @brief  弱函数测试
  * @note   
  * @param  argc: 
  * @param  *argv[]: 
  * @retval 
  */
#if 0
__attribute__((weak)) const char * weak_function_test(char * point)
{   
    printf("hello world!\n");
    return NULL;
}

int weak_func_test(void)
{
    /***
     *
     */
    char name[NAME_LEN];
    const char *s  = weak_function_test(name);
     if (NULL == s)
     {
         /* 库文件没有加载 */
         printf("ld is faild\n");
     }

    return 0;
}


#endif
