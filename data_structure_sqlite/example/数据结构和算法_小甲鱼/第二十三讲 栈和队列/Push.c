#define SATCKINCREMENT 10

Push(sqStack *s, ElemType e)
{
    // 如果栈满，追加空间
    if( s->top – s->base >= s->stackSize )
    {
        s->base = (ElemType *)realloc(s->base, (s->stackSize + STACKINCREMENT) * sizeof(ElemType));
        if( !s->base )
            exit(0);

        s->top = s->base + s->stackSize;              // 设置栈顶
        s->stackSize = s->stackSize + STACKINCREMENT; // 设置栈的最大容量
    }

    *(s->top) = e;
    s->top++;
}
