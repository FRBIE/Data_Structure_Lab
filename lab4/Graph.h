#include<stdio.h>
#include<stdlib.h>
#define MaxSize 100
int visited[MaxSize];
//邻接矩阵定义
#define MAXV 100
#define INF 0
#define InfoType int
typedef struct
{
    int no; //顶点编号
    InfoType info; //顶点其他信息
} VertexType; //顶点类型
typedef struct
{
    int edges[MAXV][MAXV]; //邻接矩阵
    int n, e; //顶点数，边数
    VertexType vexs[MAXV]; //顶点信息
} MatGraph; //图的邻接矩阵类型
//邻接表定义
typedef struct ArcNode
{
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
    InfoType info; //该弧相关信息的指针
} ArcNode; //边结点类型
typedef struct
{
    InfoType info; //顶点信息
    ArcNode *firstarc; //指向第一条依附该顶点的弧的指针
} VNode; //顶点类型
typedef struct
{
    VNode adjlist[MAXV]; //邻接表
    int n, e; //图中顶点数n和边数e
} AdjGraph; //图的邻接表类型

//建立有向图的邻接表    
void CreateAdj(AdjGraph *g);
//利用邻接表构建有向图的邻接矩阵
void AdjToMat(AdjGraph *g, MatGraph *g1);
//根据邻接表实现有向图的深度优先遍历
void DFS(AdjGraph *g, int v);
//根据邻接表实现有向图的非递归的深度优先遍历
void DFS1(AdjGraph *g, int v);
//根据邻接表实现有向图的广度优先遍历
void BFS(AdjGraph *g, int v);
//根据邻接表，输出有向图中所有从顶点v1到顶点v2的长度为n的简单路径
void PathlenAll(AdjGraph *G,int v1,int v2,int len,int path[],int d);
//根据邻接表输出有向图中从顶点v1到顶点v2的最短路径及最短长度
void ShortestPath(AdjGraph *G,int v1,int v2);
//销毁邻接表
void Destroy(AdjGraph *g);
//重置访问标记函数
void Reset(AdjGraph *g);

