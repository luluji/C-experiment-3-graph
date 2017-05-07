#include<stdio.h>
#include<stdlib.h>
#define MAXV 20
#define InfoType int
#define Vertex int

int visited1[MAXV];
int visited2[MAXV];

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

void A_DFS_MG(MGraph *g)
{
	int i;
	for(i=0;i<g->n;i++)
		if(visited1[i]==0)DFS_MG2(g,i);
	printf("\n");
}

void A_DFS_ALG(ALGraph *G)
{
	int i;
	for(i=0;i<G->n;i++)
		if(visited2[i]==0) DFS_ALG(G,i);
	printf("\n");
}

int main(void)
{
	int i,t;
	MGraph p,*g;
	g=&p;
//	MGraph *g=(MGraph *)malloc(sizeof(MGraph));
	ALGraph *G=(ALGraph *)malloc(sizeof(ALGraph));
	CreaMGraph(g);
	print_MG(g);
	printf("Input the vertex and start to traverse:");
	scanf("%d",&t);
	DFS_MG2(g,t);
	printf("\n");
	for(i=0;i<g->n;i++)
		visited1[i]=0;
	A_DFS_MG(g);

	CreaALGraph(G);
	print_ALG(G);
	printf("Input the vertex start to traverse:");
	scanf("%d",&t);
	DFS_ALG(G,t);
	printf("\n");
	for(i=0;i<G->n;i++)
		visited2[i]=0;
	A_DFS_ALG(G);
	return 0;
 }


