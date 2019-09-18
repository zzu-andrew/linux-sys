/* 头插法建立单链表示例 */

void CreateListHead(LinkList *L, int n)
{
    LinkList p;
    int i;

    srand(time(0));   // 初始化随机数种子

    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;

    for( i=0; i < n; i++ )
    {
        p = (LinkList)malloc(sizeof(Node));  // 生成新结点
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}
