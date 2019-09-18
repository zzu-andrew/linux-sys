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

