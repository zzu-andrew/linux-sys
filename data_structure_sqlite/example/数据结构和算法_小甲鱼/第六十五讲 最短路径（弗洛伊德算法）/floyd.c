#define MAXVEX	9
#define INFINITY	65535

typedef int Pathmatirx[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

void ShortestPath_Floyd(MGraph G, Pathmatirx *P, ShortPathTable *D)
{
	int v, w, k;
	
	// 初始化D和P
	for( v=0; v < G.numVertexes; v++ )
	{
		for( w=0; w < G.numVertexes; w++ )
		{
			(*D)[v][w] = G.matirx[v][w];
			(*P)[v][w] = w;
		}
	}
	
	// 优美的弗洛伊德算法
	for( k=0; k < G.numVertexes; k++ )
	{
		for( v=0; v < G.numVertexes; v++ )
		{
			for( w=0; w < G.numVertexes; w++ )
			{
				if( (*D)[v][w] > (*D)[v][k] + (*D)[k][w] )
				{
					(*D)[v][w] = (*D)[v][k] + (*D)[k][w];
					(*P)[v][w] = (*P)[v][k];		// 请思考：这里换成(*P)[k][w]可以吗？为什么？
				}
			}
		}
	}
}