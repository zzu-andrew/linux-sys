//左子树高了
#define LH 1
//相等  
#define EH 0
//
#define RH -1

typedef struct BiTNode
{
	int data;
	int bf;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

void R_Rotate(BiTree *p)
{
	BiTree L;
	L = (*p)->lchild;
	(*p)->lchild = L->rchild;
	L->rchild = (*p);
	*p = L;
	
}

void LeftBalance(BiTree *T)
{
	BiTree L, Lr;
	L = (*T)->lchild;
	
	switch(L->bf)
	{
		case LH:
			(*T)->bf = L->bf = EH;
			R_Rotate(T);
			break;
		case RH:
			Lr = L->rchild;
			switch(Lr->bf)
			{
				case LH:
					(*T)->bf = RH;
					L->bf = EH;
					break
				case EH:
					(*T)->bf = L->bf = EH;
					break;
				case RH:
					(*T)->bf = EH;
					L->bf = LH;
					break;
			}
			Lr->bf = EH;
			L_Rotate(&(*T)->lchild);
			R_Rotate(T);
	}
}

int InsertAVL(BiTree *T, int e, int *taller)
{
	if( !*T )
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		(*T)->data = e;
		(*T)->lchild = (*T)->rchild = NULL;
		(*T)->bf = EH;
		*taller = TRUE;
	}
	else
	{
		if(e == (*T)->data)
		{
			*taller = FALSE;
			return FALSE;
		}
		if(e < (*T)->data)
		{
			if(!InsertAVL(&(*T)->lchild, e, taller))
			{
				return FALSE;
			}
			if(*taller)
			{
				switch((*T)->bf)
				{
					case LH:
						LeftBalance(T);
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = LH;
						*taller = TRUE;
						break;
					case RH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
				}
			}
		}
		else
		{
			if(!InsertAVL(&(*T)->rchild, e, taller))
			{
				return FALSE;
			}
			if(*taller)
			{
				switch((*T)->bf)
				{
					case LH:
						(*T)->bf = EH;
						*taller = FALSE;
						break;
					case EH:
						(*T)->bf = RH;
						*taller = TRUE;
						break;
					case RH:
						RightBalance(T);
						*taller = FALSE;
						break;
				}
			}
		}
	}
}