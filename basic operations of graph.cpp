#include<stdio.h>
#include<stdlib.h>
#define MAXV 20
#define InfoType int
#define Vertex int

int visited1[MAXV];
int visited2[MAXV];
int d=-1;				//FindPath_ALG   length of path; for output path
int path[MAXV];	

typedef struct
{
	int no;
	InfoType info;
}VertexType;

typedef struct
{
	int edges[MAXV][MAXV];
	int n,e;
	VertexType vexs[MAXV];
}MGraph;

typedef struct ANode
{
	int adjvex;
	struct ANode *nextarc;
}ArcNode;

typedef struct
{
	Vertex data;
	ArcNode *firstarc;
}VNode;

typedef VNode AdjList[MAXV];

typedef struct
{
	AdjList adjlist;
	int n,e;
 } ALGraph;

 int getindexofvex(int no,MGraph *g)
 {
 	int i=0;
 	while(g->vexs[i].no!=no) i++;
	return i;
 }

 void CreaMGraph(MGraph *g)
 {
 	int i,j,v1,v2,no1,no2,type;
 	for(i=0;i<MAXV;i++)
 	{
 		for(j=0;j<MAXV;j++)
 		{
 			g->edges[i][j]=0;
		 }
	 }
 	do
 	{
	  	printf("Input the type of graph,Undirected graph(0) directed graph(1):");
		scanf("%d",&type);
	}while(type!=0&&type!=1);
	printf("Input vertex amount(n):");
	scanf("%d",&(g->n));
	printf("Input arc amount(e):");
	scanf("%d",&(g->e));
	for(i=0;i<g->n;i++)
	{
		printf("Input %dth vertex number:",i+1);
		scanf("%d",&(g->vexs[i].no));
	}
	for(i=0;i<g->e;i++)
	{
		printf("Input %dth edge v1 v2:",i+1);
		scanf("%d %d",&no1,&no2);
		v1=getindexofvex(no1,g);
		v2=getindexofvex(no2,g);
		if(type==0)
			g->edges[v1][v2]=g->edges[v2][v1]=1;
		else
			g->edges[v1][v2]=1;
	}
	printf("\n");
}

void insert(int v1,int v2,ALGraph *G)
{
	ArcNode *p,*q,*pre;
	p=(ArcNode *)malloc(sizeof(ArcNode));
	p->adjvex=v2;
	p->nextarc=NULL;
	q=G->adjlist[v1].firstarc;
	if(q==NULL||q!=NULL&&q->adjvex>p->adjvex)
	{
		p->nextarc=q;
		G->adjlist[v1].firstarc=p;
	}
	else
	{
		do
		{
			pre=q;
			q=q->nextarc;
		 }while(q!=NULL&&q->adjvex<p->adjvex);
		if(q!=NULL)
		{
			p->nextarc=pre->nextarc;
			pre->nextarc=p;
		}
		else
			pre->nextarc=p;
	}
}

void CreaALGraph(ALGraph *G)
{
	int i,v1,v2,type;
	for(i=0;i<MAXV;i++)
		G->adjlist[i].firstarc=NULL;
	do
	{
		printf("Input the type of graph,Undirected graph(0)directed graph(1):");
		scanf("%d",&type);
	}while(type!=0&&type!=1);
	printf("Input vertex amount(n):");
	scanf("%d",&(G->n));
	printf("Input arc amount(e):");
	scanf("%d",&(G->e));
	for(i=0;i<G->e;i++)
	{
		printf("Input %dth edge v1 v2:",i+1);
		scanf("%d %d",&v1,&v2);			
		insert(v1,v2,G);
		if(type==0&&v1!=v2)
			insert(v2,v1,G);
	}
	printf("\n");
}

void print_MG(MGraph *g)
{
	int i,j;
	printf("vertex amount:%d\n",g->n);
	printf("arc amount:%d\n",g->e);
	printf("vertex number:");
	for(i=0;i<g->n;i++)
		printf("%d ",g->vexs[i].no);
	printf("\n------------------\n");
	for(i=0;i<g->n;i++)
	{
		for(j=0;j<g->n;j++)
			printf("%d ",g->edges[i][j]);
		printf("\n");
	}
	printf("\n");
}

void print_ALG(ALGraph *G)
{
	int i,j;
	ArcNode *p;
	printf("vertex amount:%d\n",G->n);
	printf("arc amount:%d\n",G->e);
	printf("------------------\n");
	for(i=0;i<G->n;i++)
	{
   		p=G->adjlist[i].firstarc;
		for(j=0;j<G->n;j++)
		{
			if(p!=NULL&&p->adjvex==j)
			{
				printf("1 ");
				p=p->nextarc;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}

void DFS_MG1(MGraph *g,int no)
{
	int i,v;
	for(i=0;i<g->n;i++)
		visited1[i]=0;
	printf("%d",no);
	v=getindexofvex(no,g);
	visited1[v]=1;
	for(i=0;i<g->n;i++)
	{
		if(g->edges[v][i]==1&&visited1[i]==0)
			DFS_MG1(g,g->vexs[i].no);
	}

}

void DFS_MG2(MGraph *g,int v)
{
	int i;
	for(i=0;i<g->n;i++)
		visited1[i]=0;
	printf("%d",v);
	visited1[v]=1;
	for(i=0;i<g->n;i++)
	{
		if(g->edges[v][i]==1&&visited1[i]==0)
			DFS_MG2(g,i);
	}
}

void DFS_ALG(ALGraph *G,int v)
{
	ArcNode *p;
	printf("%d",v);
	visited2[v]=1;
	p=G->adjlist[v].firstarc;
	while(p!=NULL)
	{
		if(visited2[p->adjvex]==0)
			DFS_ALG(G,p->adjvex);
		p=p->nextarc;
	}
}
/*directed graph:
adjacency list:
0--1-3
1--2-3
2--3-4
3--
4--0-3
path 0 to 4: 0124
DFS:01234
reason:when u=2,d=2, next:FindaPath(G,3,4,path,2), d=3.path[3]=3, return nothing;
	   then FindaPath(G,4,4,path,2), d=3,path[3]=4, oue to u==v, return, over.	  
*/
void FindaPath_ALG(ALGraph *G,int u,int v,int path[],int d)	//path u to v
{
	int i;
	ArcNode *p;
	visited2[u]=1;
	d++;
	path[d]=u;
	if(u==v)
	{
		printf("path is:");
		for(i=0;i<=d;i++)
			printf("%d",path[i]);
		printf("\n");
		return;
	}
	p=G->adjlist[u].firstarc;
	while(p!=NULL)
	{
		if(visited2[p->adjvex]==0)
			FindaPath_ALG(G,p->adjvex,v,path,d);
		p=p->nextarc;
	}
}

void A_DFS_MG(MGraph *g)
{
	int i;
	for(i=0;i<g->n;i++)
		visited1[i]=0;
	for(i=0;i<g->n;i++)
		if(visited1[i]==0)DFS_MG2(g,i);
	printf("\n");
}

void A_DFS_ALG(ALGraph *G)
{
	int i;
	for(i=0;i<G->n;i++)
		visited2[i]=0;
	for(i=0;i<G->n;i++)
		if(visited2[i]==0) DFS_ALG(G,i);
	printf("\n");
}

void BFS(ALGraph *G,int v)
{
	int queue[MAXV];
	ArcNode *p;
	int i,t,rear=0,front=0;
	for(i=0;i<G->n;i++)
		visited2[i]=0;
	printf("%d",v);
	visited2[v]=1;
	rear++;
	queue[rear]=v;
	while(front!=rear)
	{	
		front=(front+1)%MAXV;
		t=queue[front];	
		p=G->adjlist[t].firstarc;
		while(p!=NULL)
		{		
			if(visited2[p->adjvex]==0)
			{
				printf("%d",p->adjvex);
				visited2[p->adjvex]=1;
				rear=(rear+1)%MAXV;
				queue[rear]=p->adjvex;	
			}
			p=p->nextarc;
		}
		
	}
	printf("\n");
 } 

int main(void)
{
	int i,t,u,v;
	MGraph p,*g;
	ALGraph q,*G;
	g=&p;
	G=&q;
//	MGraph *g=(MGraph *)malloc(sizeof(MGraph));
//	ALGraph *G=(ALGraph *)malloc(sizeof(ALGraph));
//	CreaMGraph(g);
//	print_MG(g);
//	printf("Input the vertex and start to DFS:");
//	scanf("%d",&t);
//	DFS_MG2(g,t);
//	printf("\n");	
//	A_DFS_MG(g);

	CreaALGraph(G);
	print_ALG(G);
	printf("Input u v:");
	scanf("%d %d",&u,&v);
	printf("\n"); 
	FindaPath_ALG(G,u,v,path,d);
//	printf("Input the vertex start to DFS:");
//	scanf("%d",&t);
//	DFS_ALG(G,t);
//	printf("\n");
//	A_DFS_ALG(G);
//	printf("Input the vertex start to BFS:");
//	BFS(G,t);
	return 0;
 }


