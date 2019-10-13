

[TOC]

# 二进制转十进制实现







```c
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


void InitStack(sqStack *s);

void Push(sqStack *s, ElemType e);

void Pop(sqStack *s, ElemType *e);

int StackLen(sqStack s);

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

void Push(sqStack *s, ElemType e)
{
    if( s->top - s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
        {
            exit(0);
        }
    }

    *(s->top) = e;
    s->top++;
}

void Pop(sqStack *s, ElemType *e)
{
    if( s->top == s->base )
    {
        return;
    }
    *e = *--(s->top); //< top指向的元素为栈顶，栈顶为下个要存数据的地方，因此、要取数据应该先下移一位之后再取出数据
}

int StackLen(sqStack s)
{
    return (s.top - s.base);
}

int main()
{
    ElemType c;
    sqStack s;
    int len, i, sum = 0;

    InitStack(&s);

    printf("请输入二进制数，输入#符号表示结束！\n");
    scanf("%c", &c);
    while( c != '#' )
    {
        Push(&s, c);
        getchar();  // 把'\n'从缓冲区去掉
        scanf("%c", &c);
    }

    len = StackLen(s);
    printf("栈的当前容量是: %d\n", len);

    for( i=0; i < len; i++ )
    {
        Pop(&s, &c);
        printf("%c\n", c);
        sum = sum + (c-48) * pow(2, i);
    }

    printf("转化为十进制数是: %d\n", sum);

    return 0;
}

```

