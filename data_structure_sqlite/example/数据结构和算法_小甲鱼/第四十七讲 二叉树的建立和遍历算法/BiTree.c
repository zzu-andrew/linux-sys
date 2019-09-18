#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode
{
	char data;
	struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

// 创建一棵二叉树，约定用户遵照前序遍历的方式输入数据
CreateBiTree(BiTree *T)
{
	char c;

	scanf("%c", &c);
	if( ' ' == c )
	{
		*T = NULL;
	}
	else
	{
		*T = (BiTNode *)malloc(sizeof(BiTNode));
		(*T)->data = c;
		CreateBiTree(&(*T)->lchild);
		CreateBiTree(&(*T)->rchild);
	}
}

// 访问二叉树结点的具体操作，你想干嘛？！
visit(char c, int level)
{
	printf("%c 位于第 %d 层\n", c, level);
}

// 前序遍历二叉树
PreOrderTraverse(BiTree T, int level)
{
	if( T )
	{
		visit(T->data, level);
		PreOrderTraverse(T->lchild, level+1);
		PreOrderTraverse(T->rchild, level+1);
	}
}

int main()
{
	int level = 1;
	BiTree T = NULL;

	CreateBiTree(&T);
	PreOrderTraverse(T, level);

	return 0;
}