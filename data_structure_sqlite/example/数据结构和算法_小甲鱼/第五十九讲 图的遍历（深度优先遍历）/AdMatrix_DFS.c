// 邻接矩阵的深度有限递归算法
// 邻接矩阵的创建代码见第五十六讲源代码部分
// 鱼C工作室(www.fishc.com)

#define TRUE 1
#define FALSE 0
#define MAX 256

typedef int Boolean;	// 这里我们定义Boolean为布尔类型，其值为TRUE或FALSE
Boolean visited[MAX];	// 访问标志的数组

void DFS(MGraph G, int i)
{
	int j;
	
	visited[j] = TRUE;			// 访问过的顶点设置为TRUE
	printf("%c ", G.vexs[i]);	// 打印顶点
	for( j=0; j < G.numVertexes; j++ )
	{
		if( G.arc[i][j]==1 && !visited[j] )
		{
			DFS(G, j);			// 对为访问的邻接顶点递归调用
		}
	}
}

// 邻接矩阵的深度遍历操作
void DFSTraverse(MGraph G)
{
	int i;
	
	for( i=0; i < G.numVertexes; i++ )
	{
		visited[i] = FALSE;		// 初始化所有顶点状态都是未访问过状态
	}
	
	for( i=0; i < G.numVertexes; i++ )
	{
		if( !visited[i] )		// 若是连通图，只会执行一次
		{
			DFS(G, i);
		}
	}
}