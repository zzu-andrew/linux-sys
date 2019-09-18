/* 初始条件：顺序线性表L已存在，1<=i<=ListLength(L) */
/* 操作结果：用e返回L中第i个数据元素的值 */

Status GetElem( LinkList L, int i, ElemType *e )
{
    int j;
    LinkList p;

    p = L->next;
    j = 1;

    while( p && j<i )
    {
        p = p->next;
        ++j;
    }

    if( !p || j>i )
    {
        return ERROR;
    }

    *e = p->data;

    return OK;
}
