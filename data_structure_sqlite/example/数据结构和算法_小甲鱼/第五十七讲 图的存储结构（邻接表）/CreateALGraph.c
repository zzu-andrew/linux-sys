#define MAXVEX 100

typedef struct EdgeNode			// 边表结点
{
	int adjvex;					// 邻接点域，存储该顶点对应的下标
	int weight;					// 用于存储权值，对于非网图可以不需要
	struct EdgeNode *next;		// 链域，指向下一个邻接点
} EdgeNode;

typedef struct VertexNode		// 顶点表结点
{
	char data;					// 顶点域，存储顶点信息
	EdgeNode *firstEdge;		// 边表头指针
} VertexNode, AdjList[MAXVEX];

typedef struct
{
	AdjList adjList;
	int numVertexes, numEdges;	// 图中当前顶点数和边数
} GraphAdjList;

// 建立图的邻接表结构
void CreateALGraph(GraphAdjList *G)
{
	int i, j, k;
	EdgeNode *e;
	
	printf("请输入顶点数和边数：\n");
	scanf("%d %d", &G->numVertexes, &G->numEdges);
	
	// 读取顶点信息，建立顶点表
	for( i=0; i < G->numVertexes; i++ )
	{
		scanf("%c", &G->adjList[i].data);
		G->adjList[i].firstEdge = NULL;		// 初始化置为空表
	}
	
	for( k=0; k < G->numEdges; k++ )
	{
		printf("请输入边(Vi,Vj)上的顶点序号：\n");
		scanf("%d %d", &i, &j);
		
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = j;						// 邻接序号为j
		e->next = G->adjList[i].firstEdge;
		G->adjList[i].firstEdge = e;
		
		e = (EdgeNode *)malloc(sizeof(EdgeNode));
		e->adjvex = i;						// 邻接序号为i
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;
	}
}