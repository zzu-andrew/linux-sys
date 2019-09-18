/*链表存储结构的定义*/
typedef struct CLinkList
{
    int data;
    struct CLinkList *next;
}node;

/*插入结点*/
/*参数：链表的第一个结点，插入的位置*/
void ds_insert(node **pNode , int i)
{
    node *temp;
    node *target;
    node *p;
    int item;
    int j = 1;

    printf("输入要插入结点的值:");
    scanf("%d", &item);

    if(i == 1)
	{ //新插入的结点作为第一个结点
        temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp->data = item;

        /*寻找到最后一个结点*/
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
			target = target->next;
		}  
		
		// target指向第三个元素的
		
		temp = (node *)malloc(sizeof(struct CLinkList));

		if(!temp)
            exit(0);

		temp->data = item;
		
        p = target->next;
        target->next = temp;
        temp->next = p;
    }
}