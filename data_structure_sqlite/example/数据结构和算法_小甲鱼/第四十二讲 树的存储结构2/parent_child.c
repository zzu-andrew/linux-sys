#define MAX_TREE_SIZE 	100

typedef char ElemType;

// 孩子结点
typedef struct CTNode
{
	int child;				// 孩子结点的下标
	struct CTNode *next;	// 指向下一个孩子结点的指针
} *ChildPtr;

// 表头结构
typedef struct
{	
	ElemType data;			// 存放在树中的结点的数据
	int parent;				// 存放双亲的下标
	ChildPtr firstchild;	// 指向第一个孩子的指针
} CTBox;

// 树结构
typedef struct
{
	CTBox nodes[MAX_TREE_SIZE];	// 结点数组
	int r, n;
}