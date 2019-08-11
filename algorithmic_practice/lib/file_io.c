#include <setjmp.h>
#include "file_io.h"

extern char **environ;


 /**
  * @brief   test IO 
  * @note   
  * @retval SUCESS"OK
  *         FAIL:ERROR
  */
int file_io_test(void)
{
    int ret = OK;
    ret |= show_environ();
    ret |= jump_func_env();
    if (ret != OK)
    {
        UNIX_DEBUG("File IO test failed!.\n");
    }

    
    return ret;
}

 /**
  * @brief   show_environ
  * @note    显示环境变量
  * @retval 
  */
int show_environ(void)
{
#if 0  ///< 打印的环境变量过长暂时进行屏蔽
    char **ep;
    UNIX_DEBUG("show eviron --------------------------------------------------!.\n");

    for (ep = environ; *ep != NULL; ep++)
        puts(*ep);
#endif
    UNIX_DEBUG("show eviron --------------------------------------------------!.\n");

    return OK;
}

static jmp_buf env;

/**
  * @brief   f2
  * @note    非局部跳转函数
  * @retval 
  */
static void f2(void)
{
    UNIX_DEBUG("f2 is running.\n");
    longjmp(env, 2);
}

/**
  * @brief   f1
  * @note    非局部跳转函数
  * @retval 
  */
static void f1(void)
{
    UNIX_DEBUG("f１ is running.\n");
    longjmp(env, 1);
}


/**
  * @brief   jump_func_env
  * @note    非局部跳转函数
  * @retval 
  */
/* 
+-----------------+     +-----------------+     +-------------------+
| setjmp init env | --> | longjmp set env | --> | setjmp return env |
+-----------------+     +-----------------+     +-------------------+
*/
int jump_func_env(void)
{
    int ret = OK;
    switch(setjmp(env))
    {
        case 0: //setjmp先初始化env，初始化之后longjmp调用之后在返回setjmp,setjmp会将longjmp设置的env返回
            f1();
            break;
        case 1:
            UNIX_DEBUG("We jumped back from f1()!.\n");
            f2();   
            break;
        case 2:
            UNIX_DEBUG("we jmmped from f2()\n");
            break;


        default:
            ret = ERROR;
            break;
    }
    return ret;
}