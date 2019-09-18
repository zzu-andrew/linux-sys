#include "stdio.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef int Status;/* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;/* ElemType类型根据实际情况而定，这里假设为int */

typedef struct Node
{
    ElemType data;
    struct Node *next;
}Node, *LinkList;

/* 初始化带头结点的空链表 */
Status InitList(LinkList *L)
{
    *L = (LinkList)malloc(sizeof(Node)); /* 产生头结点,并使L指向此头结点 */

    if(!(*L)) /* 存储分配失败 */
            return ERROR;

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

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（头插法） */
void CreateListHead(LinkList *L, int n)
{
	LinkList p;
	int i;

	srand(time(0));                         /*  初始化随机数种子 */

	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;                      /*  建立一个带头结点的单链表 */

	for (i=0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;             /*  随机生成100以内的数字 */
		p->next = (*L)->next;
		(*L)->next = p;						/*  插入到表头 */
	}
}

/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n)
{
	LinkList p,r;
	int i;

	srand(time(0));                      /* 初始化随机数种子 */
	*L = (LinkList)malloc(sizeof(Node)); /* L为整个线性表 */
	r = *L;                              /* r为指向尾部的结点 */

	for (i=0; i < n; i++)
	{
		p = (Node *)malloc(sizeof(Node)); /*  生成新结点 */
		p->data = rand()%100+1;           /*  随机生成100以内的数字 */
		r->next=p;                        /* 将表尾终端结点的指针指向新结点 */
		r = p;                            /* 将当前的新结点定义为表尾终端结点 */
	}

    r->next = (*L)->next->next;
}

// 比较步数的方法
int HasLoop1(LinkList L)
{
    LinkList cur1 = L;  // 定义结点 cur1
    int pos1 = 0;       // cur1 的步数

    while(cur1)
    {                       // cur1 结点存在
        LinkList cur2 = L;  // 定义结点 cur2
        int pos2 = 0;       // cur2 的步数
        while(cur2)
        {                           // cur2 结点不为空
            if(cur2 == cur1)
            {                       // 当cur1与cur2到达相同结点时
                if(pos1 == pos2)    // 走过的步数一样
                    break;          // 说明没有环
                else                // 否则
                {
                    printf("环的位置在第%d个结点处。\n\n", pos2);
                    return 1;       // 有环并返回1
                }
            }
            cur2 = cur2->next;      // 如果没发现环，继续下一个结点
            pos2++;                 // cur2 步数自增
        }
        cur1 = cur1->next;  // cur1继续向后一个结点
        pos1++;             // cur1 步数自增
    }
    return 0;
}

// 利用快慢指针的方法
int HasLoop2(LinkList L)
{
    int step1 = 1;
    int step2 = 2;
    LinkList p = L;
    LinkList q = L;

    while (p != NULL && q != NULL && q->next != NULL)
    {
        p = p->next;
        if (q->next != NULL)
            q = q->next->next;

        printf("p:%d, q:%d \n", p->data, q->data);

        if (p == q)
            return 1;
    }
    return 0;
}

int main()
{
    LinkList L;
    Status i;
    char opp;
    ElemType e;
    int find;
    int tmp;

    i = InitList(&L);
    printf("初始化L后：ListLength(L)=%d\n",ListLength(L));

    printf("\n1.创建有环链表（尾插法） \n2.创建无环链表（头插法） \n3.判断链表是否有环 \n0.退出 \n\n请选择你的操作：\n");
    while(opp != '0')
    {
        scanf("%c",&opp);
        switch(opp)
        {
            case '1':
                CreateListTail(&L, 10);
                printf("成功创建有环L(尾插法)\n");
                printf("\n");
                break;

            case '2':
                CreateListHead(&L, 10);
                printf("成功创建无环L(头插法)\n");
                printf("\n");
                break;

            case '3':
                printf("方法一: \n\n");
                if( HasLoop1(L) )
                {
                    printf("结论：链表有环\n\n\n");
                }
                else
                {
                    printf("结论：链表无环\n\n\n");
                }

                printf("方法二：\n\n");
                if( HasLoop2(L) )
                {
                    printf("结论：链表有环\n\n\n");
                }
                else
                {
                    printf("结论：链表无环\n\n\n");
                }
                printf("\n");
                break;

            case '0':
                exit(0);
        }
    }

}
