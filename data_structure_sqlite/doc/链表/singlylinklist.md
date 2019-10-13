[TOC]

# 单向循环链表的实现

```bash

            +-------------------------------------------------+
            v                                                 |
+---+     +---+     +---+     +---+     +---+     +---+     +---+
| 1 | --> | 2 | --> | 3 | --> | 4 | --> | 5 | --> | 6 | --> | 7 |
+---+     +---+     +---+     +---+     +---+     +---+     +---+

```

## 单向循环链表的初始化

```c
//< 初始化单向循环链表
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("初始化单向循环链表\n");

	while(1)
	{
        scanf("%d", &item);
        fflush(stdin);
        printf("item = %d\n\n", item);
		if(item == 0)
            return;

        
        if((*pNode) == NULL)
		{ 
           
			*pNode = (node*)malloc(sizeof(struct CLinkList));
			if(!(*pNode))
				exit(0);
			(*pNode)->data = item;
			(*pNode)->next = *pNode;
		}
        else
		{
            //< 指定链表为0，也要对链表进行初始化
            for(target = (*pNode); target->next != (*pNode); target = target->next)
				;

           
            temp = (node *)malloc(sizeof(struct CLinkList));

			if(!temp)
				exit(0);

			temp->data = item;
            temp->next = *pNode;
            target->next = temp;
        }
    }
}
```



## 向链表中插入一个数据

```c

void ds_insert(node **pNode , int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j = 1;

    printf("向链表中插入数据:");
    scanf("%d", &item);

    if(i == 1)
	{ 
        temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;


        for(target = (*pNode); target->next != (*pNode); target = target->next)
			;

		temp->next = (*pNode);
        target->next = temp;
        *pNode = temp;
    }
    else
	{
        target = *pNode;

        for( ; j < (i-1); ++j )
		{
			target=target->next;
		}

		temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;
        p = target->next;
        target->next = temp;
        temp->next = p;
    }
}

```

## 删除链表中的一个数据

```c

void ds_delete(node **pNode, int i)
{
    node *target;
    node *temp;
    int j = 1;

    if(i == 1)
	{ 
        for(target = *pNode; target->next != *pNode;target = target->next)
			;

		temp = *pNode;
        *pNode = (*pNode)->next;
        target->next = *pNode;
        free(temp);
    }
    else
	{
        target = *pNode;

		for( ; j < i-1; ++j )
		{
			target = target->next;
		}

		temp = target->next;
        target->next = temp->next;
        free(temp);
    }
}
```

## 查找链表中的指定的数据

```c

//< 查找链表中的指定的数据
int ds_search(node *pNode, int elem)
{
    node *target;
    int i = 1;

    for(target = pNode; target->data != elem && target->next != pNode; ++i)
	{
		target = target->next;
	}

	if(target->next == pNode) 
        return 0;
    else
        return i;
}
```





```c
#include <stdio.h>
#include <stdlib.h>


/***
 * 单向循环链表示例
 * 
 * */

typedef struct CLinkList
{
    int data;
    struct CLinkList *next;
}node;


void ds_init(node **pNode);

void ds_insert(node **pNode , int i);

void ds_delete(node **pNode, int i);

int ds_search(node *pNode, int elem);

void ds_traverse(node *pNode);

//< 初始化单向循环链表
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("初始化单向循环链表\n");

	while(1)
	{
        scanf("%d", &item);
        fflush(stdin);
        printf("item = %d\n\n", item);
		if(item == 0)
            return;

        
        if((*pNode) == NULL)
		{ 
            //< 指定的数据为0 也要对链表进行初始化
			*pNode = (node*)malloc(sizeof(struct CLinkList));
			if(!(*pNode))
				exit(0);
			(*pNode)->data = item;
			(*pNode)->next = *pNode;
		}
        else
		{
            //< 指定链表为0，也要对链表进行初始化
            for(target = (*pNode); target->next != (*pNode); target = target->next)
				;

           
            temp = (node *)malloc(sizeof(struct CLinkList));

			if(!temp)
				exit(0);

			temp->data = item;
            temp->next = *pNode;
            target->next = temp;
        }
    }
}


void ds_insert(node **pNode , int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j = 1;

    printf("向链表中插入数据:");
    scanf("%d", &item);

    if(i == 1)
	{ 
        temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;


        for(target = (*pNode); target->next != (*pNode); target = target->next)
			;

		temp->next = (*pNode);
        target->next = temp;
        *pNode = temp;
    }
    else
	{
        target = *pNode;

        for( ; j < (i-1); ++j )
		{
			target=target->next;
		}

		temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp ->data = item;
        p = target->next;
        target->next = temp;
        temp->next = p;
    }
}


void ds_delete(node **pNode, int i)
{
    node *target;
    node *temp;
    int j = 1;

    if(i == 1)
	{ 
        for(target = *pNode; target->next != *pNode;target = target->next)
			;

		temp = *pNode;
        *pNode = (*pNode)->next;
        target->next = *pNode;
        free(temp);
    }
    else
	{
        target = *pNode;

		for( ; j < i-1; ++j )
		{
			target = target->next;
		}

		temp = target->next;
        target->next = temp->next;
        free(temp);
    }
}

//< 查找链表中的指定的数据
int ds_search(node *pNode, int elem)
{
    node *target;
    int i = 1;

    for(target = pNode; target->data != elem && target->next != pNode; ++i)
	{
		target = target->next;
	}

	if(target->next == pNode) 
        return 0;
    else
        return i;
}

//< 打印处单向链表
void ds_traverse(node *pNode)
{
    node *temp;
    printf("***********链表中的数据******************\n");
    temp = pNode;
    printf("***********链表中的数据******************\n");

	do
	{
        printf("%4d ", temp->data);
    }while((temp = temp->next) != pNode);

	printf("\n");
}

int main()
{
    node *pHead = NULL;
    char opp;
    int find;

    printf("1.初始化单向循环链表 \n\n2.插入数据 \n\n3.删除一个节点 \n\n4.列出链表数据 \n\n5.打印链表数据  \n\n0.退出 \n\n请输入你的选项");
    while(opp != '0')
	{
        scanf("%c", &opp);
        switch(opp)
		{
            case '1':
                ds_init(&pHead);
                printf("\n");
                //< 如果没有初始化的链表直接使用ds_traverse 函数会造成段错误
               // ds_traverse(pHead);
                break;

            case '2':
                printf("向链表中插入数据");
                scanf("%d",  &find);
                ds_insert(&pHead, find);
                printf("插入的数据为：%d\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '3':
                printf("删除指定的链表节点");
                scanf("%d",  &find);
                ds_delete(&pHead, find);
                printf("删除的节点为： %d\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '4':
                printf("??????????????????????");
                scanf("%d",  &find);
                printf("???%d????��???%d\n",  find,  ds_search(pHead, find));
                //ListTraverse(L);
                printf("\n");
                break;

            case '5':
                ds_traverse(pHead);
                printf("\n");
                break;

            case '6':
                exit(0);
        }
    }

    return 0;
}

```

