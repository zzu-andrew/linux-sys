
int Find(int *parent, int f)
{
	while( parent[f] > 0 )
	{
		f = parent[f];
	}
	
	return f;
}

// Kruskal算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)
{
	int i, n, m;
	Edge edges[MAGEDGE];	// 定义边集数组
	int parent[MAXVEX];		// 定义parent数组用来判断边与边是否形成环路
	
	for( i=0; i < G.numVertexes; i++ )
	{
		parent[i] = 0;
	}
	
	for( i=0; i < G.numEdges; i++ )
	{
		n = Find(parent, edges[i].begin);	// 4 2 0 1 5 3 8 6 6 6 7
		m = Find(parent, edges[i].end);		// 7 8 1 5 8 7 6 6 6 7 7
		
		if( n != m )		// 如果n==m，则形成环路，不满足！
		{
			parent[n] = m;	// 将此边的结尾顶点放入下标为起点的parent数组中，表示此顶点已经在生成树集合中
			printf("(%d, %d) %d ", edges[i].begin, edges[i].end, edges[i].weight);
		}
	}
}