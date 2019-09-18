/* 尾插法建立单链表演示 */

void CreateListTail(LinkList *L, int n)
{
    LinkList p, r;
    int i;

    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    r = *L;

    for( i=0; i < n; i++ )
    {
        p = (Node *)malloc(sizeof(Node));
        p->data = rand()%100+1;
        r->next = p;
        r = p;                 // 备注：初学者可能很难理解这句，重点解释。
    }

    r->next = NULL;
}
