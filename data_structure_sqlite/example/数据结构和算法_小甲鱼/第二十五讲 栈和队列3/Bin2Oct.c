/*****************************/
/**  二进制/八进制转换器   **/
/** By www.fishc.com 小甲鱼 **/
/*****************************/

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
