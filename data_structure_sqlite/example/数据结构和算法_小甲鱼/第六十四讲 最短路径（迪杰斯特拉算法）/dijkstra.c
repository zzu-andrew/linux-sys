#define MAXVEX	9
#define	INFINITY	65535

typedef	int	Patharc[MAXVEX];			// 用于存储最短路径下标的数组
typedef int	ShortPathTable[MAXVEX];		// 用于存储到各点最短路径的权值和

void ShortestPath_Dijkstar(MGraph G, int V0, Patharc *P, ShortPathTable *D)
{
	int v, w, k, min;
	int final[MAXVEX];		// final[w] = 1 表示已经求得顶点V0到Vw的最短路径
	
	// 初始化数据
	for( v=0; v < G.numVertexes; v++ )
	{
		final[v] = 0;				// 全部顶点初始化为未找到最短路径
		(*D)[V] = G.arc[V0][v];		// 将与V0点有连线的顶点加上权值
		(*P)[V] = 0;				// 初始化路径数组P为0
	}
	(*D)[V0] = 0;		// V0至V0的路径为0
	final[V0] = 1;		// V0至V0不需要求路径
	
	// 开始主循环，每次求得V0到某个V顶点的最短路径
	for( v=1; v < G.numVertexes; v++ )
	{
		min = INFINITY;
		for( w=0; w < G.numVertexes; w++ )
		{
			if( !final[w] && (*D)[w]<min )
			{
				k = w;
				min = (*D)[w];
			}
		}
		final[k] = 1;	// 将目前找到的最近的顶点置1
		
		// 修正当前最短路径及距离
		for( w=0; w < G.numVextexes; w++ )
		{
			// 如果经过v顶点的路径比现在这条路径的长度短的话，更新！
			if( !final[w] && (min+G.arc[k][w] < (*D)[w]) )
			{
				(*D)[w] = min + G.arc[k][w];	// 修改当前路径长度
				(*p)[w] = k;					// 存放前驱顶点
			}
		}
	}
}