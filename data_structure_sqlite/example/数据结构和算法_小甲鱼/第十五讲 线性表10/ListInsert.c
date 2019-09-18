/* 在静态链表L中第i个元素之前插入新的数据元素e */

Status ListInsert( StaticLinkList L, int i, ElemType e )
{
    int j, k, l;

    k = MAX_SIZE - 1;    // 数组的最后一个元素
    if( i<1 || i>ListLength(L)+1 )
    {
        return ERROR;
    }

    j = Malloc_SLL(L);
    if( j )
    {
        L[j].data = e;
        for( l=1; l <= i-1; l++ )
        {
            k = L[k].cur;
        }
        L[j].cur = L[k].cur;
        L[k].cur = j;

        return OK;
    }

    return ERROR;
}
