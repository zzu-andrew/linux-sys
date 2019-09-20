#include "list_liner.h"


// La表示A集合，Lb表示B集合。
void unionL(List *La, list Lb)
{
    int La_len, Lb_len, i;

    ElemType e;
    La_len = ListLength(*La);
    Lb_len = ListLength(Lb);

    for( i=1; i <= Lb_len; i++ )
    {
        GetElem(Lb, i, &e);
        if( !LocateElem(*La, e) )
        {
            ListInsert(La, ++La_len, e);
        }
    }
}


/* 初始条件：顺序线性表L已存在，1<=i<=ListLength(L) */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */

Status ListInsert(LinkList *L, int i, ElemType e)
{
    int j;
    LinkList p, s;

    p = *L;
    j = 1;

    while( p && j<i )   // 用于寻找第i个结点
    {
        p = p->next;
        j++;
    }

    if( !p || j>i )
    {
        return ERROR;
    }

    s = (LinkList)malloc(sizeof(Node));
    s->data = e;

    s->next = p->next;
    p->next = s;

    return OK;
}
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

#include "stdio.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;   /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType; /* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node;

typedef struct Node *LinkList; /* 定义LinkList */

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

/* 初始化顺序线性表 */
Status InitList(LinkList *L)
{
    *L=(LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */

    if(!(*L)) /* 存储分配失败 */
    {
        return ERROR;
    }

    (*L)->next=NULL; /* 指针域为空 */

    return OK;
}

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L)
{
    int i=0;
    LinkList p=L->next; /* p指向第一个结点 */

    while(p)
    {
        i++;
        p=p->next;
    }

    return i;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L)
{
    LinkList p=L->next;

    while(p)
    {
        visit(p->data);
        p = p->next;
    }

    printf("\n");

    return OK;
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
	LinkList p,r;
	int i;

	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
	r=*L;                                /* r为指向尾部的结点 */

	for (i=0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;           /*  随机生成100以内的数字 */
		r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}

	r->next = NULL;                       /* 表示当前链表结束 */
	// 创建有环链表
    //r->next = p;
}

Status GetMidNode(LinkList L, ElemType *e)
{
    LinkList search, mid;
    mid = search = L;

    while (search->next != NULL)
    {
        //search移动的速度是 mid 的2倍
        if (search->next->next != NULL)
        {
            search = search->next->next;
            mid = mid->next;
        }
        else
        {
            search = search->next;
        }
    }

    *e = mid->data;

    return OK;
}

int main()
{
    LinkList L;
    Status i;
    char opp;
    ElemType e;
    int find;
    int tmp;

    i=InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));

    printf("\n1.查看链表 \n2.创建链表（尾插法） \n3.链表长度 \n4.中间结点值 \n0.退出 \n请选择你的操作：\n");
    while(opp != '0')
    {
        scanf("%c",&opp);
        switch(opp)
        {
            case '1':
                ListTraverse(L);
                printf("\n");
                break;

            case '2':
                CreateListTail(&L,20);
                printf("整体创建L的元素(尾插法)：\n");
                ListTraverse(L);
                printf("\n");
                break;

            case '3':
                //clearList(pHead);   //清空链表
                printf("ListLength(L)=%d \n",ListLength(L));
                printf("\n");
                break;

            case '4':
                //GetNthNodeFromBack(L,find,&e);
                GetMidNode(L, &e);
                printf("链表中间结点的值为：%d\n", e);
                //ListTraverse(L);
                printf("\n");
                break;

            case '0':
                exit(0);
        }
    }
}



Status GetMidNode(LinkList L, ElemType *e)
{
    LinkList search, mid;
    mid = search = L;

    while (search->next != NULL)
    {
        //search移动的速度是 mid 的2倍
        if (search->next->next != NULL)
        {
            search = search->next->next;
            mid = mid->next;
        }
        else
        {
            search = search->next;
        }
    }

    *e = mid->data;

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


Status ClearList(LinkList *L)
{
    LinkList p, q;

    p = (*L)->next;

    while(p)
    {
        q = p->next;
        free(p);
        p = q;
    }

    (*L)->next = NULL;

    return OK;
}


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

/* 初始条件：顺序线性表L已存在，1<=i<=ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度-1 */

Status ListDelete(LinkList *L, int i, ElemType *e)
{
    int j;
    LinkList p, q;

    p = *L;
    j = 1;

    while( p->next && j<i )
    {
        p = p->next;
        ++j;
    }

    if( !(p->next) || j>i )
    {
        return ERROR;
    }

    q = p->next;
    p->next = q->next;

    *e = q->data;
    free(q);

    return OK;
}

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


// Status 是函数的类型，其值是函数结果状态代码，如OK等。
// 初始条件：顺序线性表L已存在，1 <= i <= ListLength(L)
// 操作结果：用e返回L中第i个数据元素的值。

Status GetElem(SqList L, int i, ElemType *e)
{
    if( L.length==0 || i<1 || i>L.length )
    {
        return ERROR;
    }
    *e = L.data[i-1];

    return OK;
}


/* 初始条件：顺序线性表L已存在，1<=i<=ListLength(L)。 */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L长度+1。*/

Status ListInsert(SqList *L, int i, ElemType e)
{
    int k;

    if( L->length == MAXSIZE )  // 顺序线性表已经满了
    {
        return ERROR;
    }
    if( i<1 || i>L->length+1)   // 当i不在范围内时
    {
        return ERROR;
    }
    if( i <= L->length )   // 若插入数据位置不在表尾
    {
        /* 将要插入位置后数据元素向后移动一位 */
        for( k=L->length-1; k >= i-1; k-- )
        {
            L->data[k+1] = L->data[k];
        }
    }

    L->data[i-1] = e;  // 将新元素插入
    L->length++;

    return OK;
}
