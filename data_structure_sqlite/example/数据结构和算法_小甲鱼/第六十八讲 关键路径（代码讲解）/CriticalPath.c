// 边表结点声明
typedef struct EdgeNode
{
	int adjvex;
	struct EdgeNode *next;
}EdgeNode;

// 顶点表结点声明
typedef struct VertexNode
{
	int in;			// 顶点入度
	int data;
	EdgeNode *firstedge;
}VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges;
}graphAdjList, *GraphAdjList;

int *etv, *ltv;
int *stack2;			// 用于存储拓扑序列的栈
int top2;				// 用于stack2的栈顶指针

// 拓扑排序算法
// 若GL无回路，则输出拓扑排序序列并返回OK，否则返回ERROR
Status TopologicalSort(GraphAdjList GL)
{
	EdgeNode *e;
	int i, k, gettop;
	int top = 0;		// 用于栈指针下标索引
	int count = 0;		// 用于统计输出顶点的个数
	int *stack;			// 用于存储入度为0的顶点
	
	stack = (int *)malloc(GL->numVertexes * sizeof(int));
	
	for( i=0; i < GL->numVertexes; i++ )
	{
		if( 0 == GL->adjList[i].in )
		{
			stack[++top] = i;	// 将度为0的顶点下标入栈
		}
	}
	
	// 初始化etv都为0
	top2 = 0;
	etv = (int *)malloc(GL->numVertexes*sizeof(int));
	for( i=0; i < GL->numVertexes; i++ )
	{
		etv[i] = 0;
	}
	stack2 = (int *)malloc(GL->numVertexes*sizeof(int));
	
	while( 0 != top )
	{
		gettop = stack[top--];		// 出栈
		// printf("%d -> ", GL->adjList[gettop].data); 
		stack2[++top2] = gettop;	// 保存拓扑序列顺序 C1 C2 C3 C4 .... C9
		count++;				
		
		for( e=GL->adjList[gettop].firstedge; e; e=e->next )
		{
			k = e->adjvex;
			// 注意：下边这个if条件是分析整个程序的要点！
			// 将k号顶点邻接点的入度-1，因为他的前驱已经消除
			// 接着判断-1后入度是否为0，如果为0则也入栈
			if( !(--GL->adjList[k].in) )	
			{
				stack[++top] = k;
			}
			
			if( (etv[gettop]+e->weight) > etv[k] )
			{
				etv[k] = etv[gettop] + e->weight;
			}
		}
	}
	
	if( count < GL->numVertexes )	// 如果count小于顶点数，说明存在环
	{
		return ERROR;
	}
	else
	{
		return OK;
	}
}

// 求关键路径，GL为有向图，输出GL的各项关键活动
void CriticalPath(GraphAdjList GL)
{
	EdgeNode *e;
	int i, gettop, k, j;
	int ete, lte;
	
	// 调用改进后的拓扑排序，求出etv和stack2的值
	TopologicalSort(GL);
	
	// 初始化ltv都为汇点的时间
	ltv = (int *)malloc(GL->numVertexes*sizeof(int));
	for( i=0; i < GL->numVertexes; i++ )
	{
		ltv[i] = etv[GL->numVertexes-1];
	}
	
	// 从汇点倒过来逐个计算ltv
	while( 0 != top2 )
	{
		gettop = stack2[top2--];	// 注意，第一个出栈是汇点
		for( e=GL->adjList[gettop].firstedge; e; e=e->next )
		{
			k = e->adjvex;
			if( (ltv[k] - e->weight) < ltv[gettop] )
			{
				ltv[gettop] = ltv[k] - e->weight;
			}
		}
	}
	
	// 通过etv和ltv求ete和lte
	for( j=0; j < GL->numVertexes; j++ )
	{
		for( e=GL->adjList[j].firstedge; e; e=e->next )
		{
			k = e->adjvex;
			ete = etv[j];
			lte = ltv[k] - e->weight;
			
			if( ete == lte )
			{
				printf("<v%d,v%d> length: %d , ", GL->adjList[j].data, GL->adjList[k].data, e->weight );
			}
		}
	}
}