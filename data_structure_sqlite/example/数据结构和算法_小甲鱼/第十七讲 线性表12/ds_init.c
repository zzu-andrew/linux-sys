/*初始化循环链表*/
void ds_init(node **pNode)
{
    int item;
    node *temp;
    node *target;

    printf("输入结点的值，输入0完成初始化\n");

	while(1)
	{
        scanf("%d", &item);
        fflush(stdin);

		if(item == 0)
            return;

        if((*pNode) == NULL)
		{ /*循环链表中只有一个结点*/
			*pNode = (node*)malloc(sizeof(struct CLinkList));
			
			if(!(*pNode))
				exit(0);
			
			(*pNode)->data = item;
			(*pNode)->next = *pNode;
		}
        else
		{
            /*找到next指向第一个结点的结点*/
            for(target = (*pNode); target->next != (*pNode); target = target->next)
				;

            /*生成一个新的结点*/
            temp = (node *)malloc(sizeof(struct CLinkList));

			if(!temp)
				exit(0);

			temp->data = item;
            temp->next = *pNode;
            target->next = temp;
        }
    }
}