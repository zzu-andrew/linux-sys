// 邻接表的深度有限递归算法
// 邻接表的创建代码见第五十七讲源代码部分
// 鱼C工作室(www.fishc.com)

#define TRUE 1
#define FALSE 0
#define MAX 256

typedef int Boolean;	// 这里我们定义Boolean为布尔类型，其值为TRUE或FALSE
Boolean visited[MAX];	// 访问标志的数组

void DFS(GraphAdjList GL, int i)
{
	EdgeNode *p;
	
	visited[i] = TRUE;
	printf("%c " GL->adjList[i].data);
	p = GL->adjList[i].firstEdge;
	
	while(p)
	{
		if( !visited[p->adjvex] )
		{
			DFS(GL, p->adjvex);
		}
		p = p->next;
	}
}

// 邻接表的深度遍历操作
void DFSTraverse(GraphAdjList GL)
{
	int i;
	
	for( i=0; i < GL->numVertexes; i++ )
	{
		visited[i] = FALSE;		// 初始化所有顶点状态都是未访问过状态
	}
	
	for( i=0; i < GL->numVertexes; i++ )
	{
		if( !visited[i] )		// 若是连通图，只会执行一次
		{
			DFS(GL, i);
		}
	}
}