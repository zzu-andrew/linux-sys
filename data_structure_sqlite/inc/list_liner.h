#ifndef __LIST_LINER__
#define __LIST_LINER__
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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

Status visit(ElemType c);



/* 初始化顺序线性表 */
Status InitList(LinkList *L);

/* 初始条件：顺序线性表L已存在。操作结果：返回L中数据元素个数 */
int ListLength(LinkList L);


/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(LinkList L);


/*  随机产生n个元素的值，建立带表头结点的单链线性表L（尾插法） */
void CreateListTail(LinkList *L, int n);


Status GetMidNode(LinkList L, ElemType *e);



#endif  //< __LIST_LINER__