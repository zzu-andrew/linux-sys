/* 删除在L中的第i个数据元素 */
Status ListDelete(StaticLinkList L, int i)
{
    int j, k;

    if( i<1 || i>ListLength(L) )
    {
        return ERROR;
    }

    k = MAX_SIZE - 1;

    for( j=1; j <= i-1; j++ )
    {
        k = L[k].cur;    // k1 = 1, k2 = 5
    }

    j = L[k].cur;        // j = 2
    L[k].cur = L[j].cur;

    Free_SLL(L, j);

    return OK;
}

/* 将下标为k的空闲结点回收到备用链表 */
void Free_SLL(StaticLinkList space, int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

/* 返回L中数据元素个数 */
int ListLength(StaticLinkList L)
{
    int j = 0;
    int i = L[MAXSIZE-1].cur;

    while(i)
    {
        i = L[i].cur;
        j++;
    }

    return j;
}
