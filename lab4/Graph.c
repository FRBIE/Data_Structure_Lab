#include"Graph.h"
//建立有向图的邻接表   
void CreateAdj(AdjGraph *g)
{
    int i, j, k;
    ArcNode *p; //边结点指针
    printf("请输入顶点数和边数："); 
    scanf("%d%d", &g->n, &g->e);
    printf("请输入顶点信息：");
    for (i = 0; i < g->n; i++)
    {
        scanf("%d", &g->adjlist[i].info);
        g->adjlist[i].firstarc = NULL;
    }
    printf("请输入边的信息：\n");
    for (k = 0; k < g->e; k++)
    {
        printf("请输入边(vi,vj)的下标i,下标j");
        scanf("%d%d", &i, &j);
        p = (ArcNode *)malloc(sizeof(ArcNode)); 
        p->adjvex = j;  
        p->nextarc = g->adjlist[i].firstarc;    
        g->adjlist[i].firstarc = p; 
    }
}
//利用邻接表构建有向图的邻接矩阵
void AdjToMat(AdjGraph *g, MatGraph *g1)
{
    int i, j;   //顶点编号
    ArcNode *p; //边结点指针     
    g1->n = g->n;       //顶点数
    g1->e = g->e;    //边数
    for (i = 0; i < g1->n; i++) //顶点信息
    {
        g1->vexs[i].no = g->adjlist[i].info;    //顶点编号
    }
    for (i = 0; i < g1->n; i++) //邻接矩阵初始化
    {
        for (j = 0; j < g1->n; j++) //边的权值
        {
            g1->edges[i][j] = INF;  //无穷大
        }
    }
    for (i = 0; i < g1->n; i++) //邻接矩阵赋值
    {
        p = g->adjlist[i].firstarc; //p指向顶点i的第一条边
        while (p != NULL)   //p不空循环
        {
            g1->edges[i][p->adjvex] = 1;    //边的权值
            p = p->nextarc; //p指向顶点i的下一条边
        }
    }
}
//根据邻接表实现有向图的深度优先遍历
void DFS(AdjGraph *g, int v)
{
    int i;  //顶点编号
    ArcNode *p; //边结点指针
    printf("%d", v);   //访问顶点v 
    visited[v] = 1;     //置已访问标记
    p = g->adjlist[v].firstarc; //p指向顶点v的第一条边
    while (p != NULL)   //p不空循环
    {
        i = p->adjvex;  //i为顶点v的邻接点编号
        if (visited[i] == 0)    //若i未访问
        {
            DFS(g, i);  //递归调用DFS
        }
        p = p->nextarc; //p指向顶点v的下一条边
    }
}
//根据邻接表实现有向图的非递归的深度优先遍历
void DFS1(AdjGraph *g, int v)
{
    int i;  //顶点编号
    ArcNode *p; //边结点指针
    int stack[MaxSize], top = -1;   //定义栈
    printf("%d", v);   //访问顶点v 
    visited[v] = 1;     //置已访问标记
    top++;  //进栈
    stack[top] = v; //顶点v入栈
    while (top != -1)   //栈不空循环
    {
        v = stack[top]; //出栈
        top--;  //栈顶指针减1
        p = g->adjlist[v].firstarc; //p指向顶点v的第一条边
        while (p != NULL)   //p不空循环
        {
            i = p->adjvex;  //i为顶点v的邻接点编号
            if (visited[i] == 0)    //若i未访问
            {
                printf("%d", i);    //访问顶点i
                visited[i] = 1;     //置已访问标记
                top++;  //进栈
                stack[top] = i; //顶点i入栈
                p = g->adjlist[i].firstarc; //p指向顶点i的第一条边
            }
            else    //若i已访问
            {
                p = p->nextarc; //p指向顶点v的下一条边
            }
        }
    }
}
//根据邻接表实现有向图的广度优先遍历
void BFS(AdjGraph *g, int v)
{
    int i;//顶点编号
    ArcNode *p;//边结点指针
    int queue[MaxSize], front = 0, rear = 0;//定义队列
    printf("%d", g->adjlist[v].info);//访问顶点v
    visited[v] = 1;//置已访问标记
    rear = (rear + 1) % MaxSize;//进队
    queue[rear] = v;//顶点v入队
    while (front != rear)//队不空循环
    {
        front = (front + 1) % MaxSize;//出队
        v = queue[front];//出队顶点编号
        p = g->adjlist[v].firstarc;//取顶点v的第一条边
        while (p != NULL)//依次检查v的所有边
        {
            i = p->adjvex;//取边顶点编号
            if (visited[i] == 0)    //若顶点i未访问
            {
                printf("%d", g->adjlist[i].info);//访问顶点i
                visited[i] = 1;//置已访问标记
                rear = (rear + 1) % MaxSize;//进队
                queue[rear] = i;//顶点i入队
            }
            p = p->nextarc;//取下一条边
        }
    }
}
//根据邻接表，输出有向图中所有从顶点v1到顶点v2的长度为n的简单路径
void PathlenAll(AdjGraph *G,int v1,int v2,int len,int path[],int d)
{
    int w,i;//w为顶点v1的邻接点，i为循环变量
    ArcNode *p; //边结点指针
    visited[v1]=1;  //置已访问标记
    d++;path[d]=v1;   //将顶点v1加入到path中
    if(v1==v2&&d==len)  //找到一条长度为len的路径
    {
        for(i=0;i<=d;i++)   //输出路径
        {
            printf("%d",path[i]);   
        }
        printf("\n");
    }
    p=G->adjlist[v1].firstarc;  //p指向顶点v1的第一条边
    while(p!=NULL)  //p不空循环
    {
        w=p->adjvex;    //w为顶点v1的邻接点
        if(visited[w]==0)   //若w未访问
        {
            PathlenAll(G,w,v2,len,path,d);  //递归调用PathlenAll
        }
        p=p->nextarc;   //p指向顶点v1的下一条边
    }
    visited[v1]=0;  //置已访问标记
}
void ShortestPath(AdjGraph *G,int v1,int v2)
{
    
    /**
     * 总体简要思路：
     * 1.首先初始化dist数组，dist[i]表示源点到顶点i的最短路径长度，初始化为10000
     * 2.初始化path数组，path[i]表示顶点i的前驱顶点，初始化为-1
     * 3.初始化visited数组，visited[i]表示顶点i是否被访问，初始化为0
     * 4.将源点v1的dist[v1]置为0，path[v1]置为-1，visited[v1]置为1
     * 5.将源点v1的邻接点的dist置为1，path置为v1，visited置为1
     * 6.循环n次，每次找到未访问的最近顶点，将其visited置为1，将其邻接点的dist置为源点到该邻接点的距离，将其邻接点的path置为该顶点，直到循环结束
     * 7.输出dist[v2]即为最短路径长度
     * 8.输出最短正向路径，从终点v2开始，依次输出path[v2]，直到path[v2]为-1
     * 
    */
    int i,j,k;  //循环变量
    int path[MAXV]; //存放一条路径
    int dist[MAXV]; //存放路径长度
    int mindis; //最短路径长度
    ArcNode *p; //边结点指针
    int output[MAXV]; //存放路径
    int count = 0; //路径长度
    for(i=0;i<G->n;i++) 
    {
        dist[i]=10000;//初始化距离
    }
    dist[v1]=0; //源点到源点的距离为0
    path[v1]=-1;    //源点的前驱为-1
    visited[v1]=1;  //置已访问标记
    p=G->adjlist[v1].firstarc;  //p指向顶点v1的第一条边
    while(p!=NULL)  //p不空循环
    {
        dist[p->adjvex]=1;  //源点到顶点v1的邻接点的距离为1
        path[p->adjvex]=v1; //顶点v1为顶点v1的邻接点的前驱
        p=p->nextarc;
    }
    for(i=0;i<G->n;i++) 
    {
        mindis=10000;   //初始化最短路径长度
        for(j=0;j<G->n;j++) //找到未访问的最近顶点
        {
            if(visited[j]==0&&dist[j]<mindis)           
            {
                k=j;    //k为未访问的最近顶点
                mindis=dist[j]; //更新最短路径长度
            }   
        }
        visited[k]=1;   //置已访问标记
        p=G->adjlist[k].firstarc;   //p指向顶点k的第一条边
        while(p!=NULL)  //p不空循环
        {
            if(visited[p->adjvex]==0&&dist[k]+1<dist[p->adjvex])    //修改源点到未访问顶点的距离
            {
                dist[p->adjvex]=dist[k]+1;  //修改最短路径长度
                path[p->adjvex]=k;  //修改顶点的前驱
            }
            p=p->nextarc;   //p指向顶点k的下一条边
        }
    }
    printf("最短路径长度为：%d\n",dist[v2]);    //输出最短路径长度
    printf("最短正向路径为：");   //输出最短正向路径
    i=v2;   //i为终点
    while(i!=-1)    
    {
        output[count] = i;
        count++;
        i=path[i];  //i的前驱为下一个顶点
    }
    for (i = count - 1; i >= 0; i--) {
        printf("%d", output[i]);
    }
    printf("\n");   
}
//销毁邻接表
void Destroy(AdjGraph *g)
{
    int i;
    ArcNode *pre, *p;
    for (i = 0; i < g->n; i++)
    {
        pre = g->adjlist[i].firstarc;
        if (pre != NULL)
        {
            p = pre->nextarc;
            while (p != NULL)
            {
                free(pre);
                pre = p;
                p = p->nextarc;
            }
        }
    }
}
//重置访问标记函数
void Reset(AdjGraph *g)
{
    int i;
    for (i = 0; i < g->n; i++)
    {
        visited[i] = 0;
    }
}
//输出邻接矩阵
void Print(MatGraph *g)
{
    int i, j;
    for (i = 0; i < g->n; i++)
    {
        for (j = 0; j < g->n; j++)
        {
            printf("%d ", g->edges[i][j]);
        }
        printf("\n");
    }
}

//主函数
int main(){
    //以菜单形式展示各种运算
    //1.建立有向图的邻接表 
    //2.利用邻接表构建有向图的邻接矩阵
    //3.根据邻接表实现深度优先遍历
    //4.根据邻接表实现非递归的深度优先遍历
    //5.根据邻接表实现广度优先遍历
    //6.输出从顶点v1到顶点v2的所有长度为n的简单路径
    //7.输出从顶点v1到顶点v2的最短路径
    //8.销毁邻接表
    //9.退出
    //初始化visited数组
    for (int i = 0; i < MAXV; i++)
    {
        visited[i] = 0;
    }
    //定义所需变量
        //path数组
    int path[MAXV];
    int choice;
    int v1, v2, n;
    AdjGraph *g;
    g = (AdjGraph *)malloc(sizeof(AdjGraph));
    MatGraph *g1;
    g1 = (MatGraph *)malloc(sizeof(MatGraph));
    //打印菜单并调用相关函数
    printf("1.建立有向图的邻接表\n");
    printf("2.利用邻接表构建有向图的邻接矩阵\n");
    printf("3.根据邻接表实现深度优先遍历\n");
    printf("4.根据邻接表实现非递归的深度优先遍历\n");
    printf("5.根据邻接表实现广度优先遍历\n");
    printf("6.输出从顶点v1到顶点v2的所有长度为n的简单路径\n");
    printf("7.输出从顶点v1到顶点v2的最短路径\n");
    printf("8.销毁邻接表\n");
    printf("9.退出\n");
    printf("请输入你的选择：");
    scanf("%d", &choice);
    while(choice!=9)
    {
        switch(choice){
            case 1:
                CreateAdj(g);
                break;
            case 2:
                AdjToMat(g, g1);
                Print(g1);
                break;
            case 3:
                printf("请输入遍历的起始顶点：");
                scanf("%d", &v1);
                printf("深度优先遍历的结果为：");
                DFS(g, v1);
                printf("\n");
                Reset(g);
                break;
            case 4:
                printf("请输入遍历的起始顶点：");
                scanf("%d", &v1);
                printf("非递归的深度优先遍历的结果为：");
                DFS1(g, v1);
                printf("\n");
                Reset(g);
                break;
            case 5:
                printf("请输入遍历的起始顶点：");
                scanf("%d", &v1);
                printf("广度优先遍历的结果为：");
                BFS(g, v1);
                printf("\n");
                Reset(g);
                break;
            case 6:
                printf("请输入起始顶点v1：");
                scanf("%d", &v1);
                printf("请输入终止顶点v2：");
                scanf("%d", &v2);
                printf("请输入路径长度n：");
                scanf("%d", &n);
                
                printf("从顶点%d到顶点%d的所有长度为%d的简单路径为：\n", v1, v2, n);
                PathlenAll(g, v1, v2, 3,path,-1);
                printf("\n");
                break;
            case 7:
                printf("请输入起始顶点v1：");
                scanf("%d", &v1);
                printf("请输入终止顶点v2：");
                scanf("%d", &v2);
                ShortestPath(g, v1, v2);
                Reset(g);
                break;
            case 8: 
                Destroy(g);
                break;
            case 9:
                break;
            default:
                printf("输入错误，请重新输入！\n");
                break;
        }
        printf("1.建立有向图的邻接表\n");
        printf("2.利用邻接表构建有向图的邻接矩阵\n");
        printf("3.根据邻接表实现深度优先遍历\n");
        printf("4.根据邻接表实现非递归的深度优先遍历\n");
        printf("5.根据邻接表实现广度优先遍历\n");
        printf("6.输出从顶点v1到顶点v2的所有长度为n的简单路径\n");
        printf("7.输出从顶点v1到顶点v2的最短路径\n");
        printf("8.销毁邻接表\n");
        printf("9.退出\n");
        printf("请输入你的选择：");
        scanf("%d", &choice);
    }
    return 0;
}

