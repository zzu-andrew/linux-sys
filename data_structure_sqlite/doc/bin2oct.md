[TOC]





# 二进制转换为八进制

​	二进制转换为八进制，需要使用两个栈，一个栈用于存储二进制数据，另一个栈用于存储八进制数据。

​	每三个二进制数据代表一个八进制数据。因此，需要弹出三个二进制数据并将其转换为对应的八进制，然后在将八进制数据压栈。



```c

/**********************************************************
 * @ 二进制转换为八进制 
 * 二进制转换为八进制，需要两个栈来实现，一个栈用于存储二进制数，
 * 另一个用于存储八进制数，二进制的每三位代表八进制的一位，弹出二进制
 * 的三位将其转换为八进制放入到八进制的栈中
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 20
#define STACKINCREMENT  10

typedef char ElemType;
typedef struct
{
    ElemType *base;
    ElemType *top;
    int stackSize;
}sqStack;

/**
 * @brief  初始化栈
 * @note   
 * @param  *s: 栈的地址
 * @retval None
 */
void InitStack(sqStack *s);

/**
 * @brief  压栈操作
 * @note   
 * @param  *s: 栈的地址
 * @param  e: 压栈的数据
 * @retval None
 */
void Push(sqStack *s, ElemType e);

/**
 * @brief  出栈操作
 * @note   
 * @param  *s: 栈的地址
 * @param  *e: 出栈的元素
 * @retval None
 */
void Pop(sqStack *s, ElemType *e);


/**
 * @brief  计算栈的长度
 * @note   
 * @param  s: 栈
 * @retval 
 */
int StackLen(sqStack s);

// 函数功能：初始化栈
// 参数*s：栈的地址
void InitStack(sqStack *s)
{
    s->base = (ElemType *)malloc(STACK_INIT_SIZE * sizeof(ElemType));
    if( !s->base )
    {
        exit(0);
    }

    s->top = s->base;
    s->stackSize = STACK_INIT_SIZE;
}

// 函数功能：入栈操作
// 参数*s：栈的地址
// 参数e：待压入栈的元素
void Push(sqStack *s, ElemType e)
{
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
        {
            exit(0);
        }

        s->top = s->base + s->stackSize;
        s->stackSize = s->stackSize + STACKINCREMENT;
    }

    *(s->top) = e;
    s->top++;
}

// 函数功能：弹栈操作
// 参数*s：栈的地址
// 参数e：存放从栈里弹出的数据
void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top);
}

// 函数功能：计算栈s的当前长度
// 参数s：栈
int StackLen(sqStack s)
{
    return (s.top - s.base);
}

int main()
{
    ElemType c;
    sqStack s1;
    sqStack s2;
    int len, i, j, sum = 0;

    InitStack(&s1); // 初始化栈s1，用来存放二进制输入

    printf("请输入二进制数，输入‘#’号表示结束！\n\n");
    scanf("%c", &c);
    while( c != '#' )
    {
        if( c=='0' || c=='1' )  // 检查输入是否二进制
            Push(&s1, c);
        scanf("%c", &c);
    }
    getchar();      // 把'\n'从缓冲区去掉
    len = StackLen(s1);
    printf("二进制栈的大小为: %d\n", len);

    InitStack(&s2); // 初始化栈s2，用来存放转换的八进制

    for( i=0; i < len; i+=3 )
    {
        for( j=0; j < 3; j++ )
        {
            Pop( &s1, &c ); // 取出栈顶元素
            sum = sum + (c-48) * pow(2, j);

            if( s1.base == s1.top )
            {
                break;
            }
        }

        Push( &s2, sum+48 );
        sum = 0;
    }

    printf("\n转化为八进制数是: ");
    while( s2.base != s2.top )
    {
        Pop( &s2, &c );
        printf("%c", c);
    }
    printf("(O)\n");

    return 0;
}

```

