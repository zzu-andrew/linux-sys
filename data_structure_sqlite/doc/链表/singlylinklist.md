[TOC]

# 鍗曞悜寰幆閾捐〃鐨勫疄鐜�

```bash

            +-------------------------------------------------+
            v                                                 |
+---+     +---+     +---+     +---+     +---+     +---+     +---+
| 1 | --> | 2 | --> | 3 | --> | 4 | --> | 5 | --> | 6 | --> | 7 |
+---+     +---+     +---+     +---+     +---+     +---+     +---+

```

## 鍗曞悜寰幆閾捐〃鐨勫垵濮嬪寲

```c
//< 鍒濆鍖栧崟鍚戝惊鐜摼琛�
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("鍒濆鍖栧崟鍚戝惊鐜摼琛╘n");

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
            //< 鎸囧畾閾捐〃涓�0锛屼篃瑕佸閾捐〃杩涜鍒濆鍖�
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



## 鍚戦摼琛ㄤ腑鎻掑叆涓€涓暟鎹�

```c

void ds_insert(node **pNode , int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j = 1;

    printf("鍚戦摼琛ㄤ腑鎻掑叆鏁版嵁:");
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

## 鍒犻櫎閾捐〃涓殑涓€涓暟鎹�

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

## 鏌ユ壘閾捐〃涓殑鎸囧畾鐨勬暟鎹�

```c

//< 鏌ユ壘閾捐〃涓殑鎸囧畾鐨勬暟鎹�
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
 * 鍗曞悜寰幆閾捐〃绀轰緥
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

//< 鍒濆鍖栧崟鍚戝惊鐜摼琛�
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("鍒濆鍖栧崟鍚戝惊鐜摼琛╘n");

	while(1)
	{
        scanf("%d", &item);
        fflush(stdin);
        printf("item = %d\n\n", item);
		if(item == 0)
            return;

        
        if((*pNode) == NULL)
		{ 
            //< 鎸囧畾鐨勬暟鎹负0 涔熻瀵归摼琛ㄨ繘琛屽垵濮嬪寲
			*pNode = (node*)malloc(sizeof(struct CLinkList));
			if(!(*pNode))
				exit(0);
			(*pNode)->data = item;
			(*pNode)->next = *pNode;
		}
        else
		{
            //< 鎸囧畾閾捐〃涓�0锛屼篃瑕佸閾捐〃杩涜鍒濆鍖�
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

    printf("鍚戦摼琛ㄤ腑鎻掑叆鏁版嵁:");
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

//< 鏌ユ壘閾捐〃涓殑鎸囧畾鐨勬暟鎹�
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

//< 鎵撳嵃澶勫崟鍚戦摼琛�
void ds_traverse(node *pNode)
{
    node *temp;
    printf("***********閾捐〃涓殑鏁版嵁******************\n");
    temp = pNode;
    printf("***********閾捐〃涓殑鏁版嵁******************\n");

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

    printf("1.鍒濆鍖栧崟鍚戝惊鐜摼琛� \n\n2.鎻掑叆鏁版嵁 \n\n3.鍒犻櫎涓€涓妭鐐� \n\n4.鍒楀嚭閾捐〃鏁版嵁 \n\n5.鎵撳嵃閾捐〃鏁版嵁  \n\n0.閫€鍑� \n\n璇疯緭鍏ヤ綘鐨勯€夐」");
    while(opp != '0')
	{
        scanf("%c", &opp);
        switch(opp)
		{
            case '1':
                ds_init(&pHead);
                printf("\n");
                //< 濡傛灉娌℃湁鍒濆鍖栫殑閾捐〃鐩存帴浣跨敤ds_traverse 鍑芥暟浼氶€犳垚娈甸敊璇�
               // ds_traverse(pHead);
                break;

            case '2':
                printf("鍚戦摼琛ㄤ腑鎻掑叆鏁版嵁");
                scanf("%d",  &find);
                ds_insert(&pHead, find);
                printf("鎻掑叆鐨勬暟鎹负锛�%d\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '3':
                printf("鍒犻櫎鎸囧畾鐨勯摼琛ㄨ妭鐐�");
                scanf("%d",  &find);
                ds_delete(&pHead, find);
                printf("鍒犻櫎鐨勮妭鐐逛负锛� %d\n",  find);
                ds_traverse(pHead);
                printf("\n");
                break;

            case '4':
                printf("??????????????????????");
                scanf("%d",  &find);
                printf("???%d????锟斤拷???%d\n",  find,  ds_search(pHead, find));
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

