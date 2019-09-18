//假设A，B为非空循环链表的尾指针
LinkList Connect(LinkList A,LinkList B)
{	
	LinkList p = A->next;		//保存A表的头结点位置
	
	A->next = B->next->next;	//B表的开始结点链接到A表尾
	
	free(B->next);	//释放B表的头结点,初学者容易忘记
	
	B->next = p;		
	
	return B;		//返回新循环链表的尾指针
} 
