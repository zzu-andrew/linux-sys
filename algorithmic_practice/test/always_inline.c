#include "sys_tem.h"

#if 0
/**	用always_inline属性修饰函数func	*/
static	int	__attribute__((always_inline))	func(void)
{
				return	100;
}
int	always_inline_test(void)
{
    //	这里对func的函数调用会被内联
    int	a	=	func();
    
    //	这里获取func的地址也完全没问题
    int	(*pFunc)(void)	=	&func;
    printf("func	address:	0x%.16zX\n",	(size_t)pFunc);
    
    a	+=	pFunc();
    printf("a	=	%d\n",	a);
    return OK;
}

#endif