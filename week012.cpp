#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct Node
{
	int index;
	int degree;	
	Node* sons[105];
	Node()
	{
		degree=0;
		for(int i=0;i<105;i++)
			sons[i]=NULL;
	}
};

int n,m;
int v[105];
int edge[105][105]={0};
Node* nodes[105]={NULL};
Node rawnodes[105];
int ans[105][105][105]={0};

void dp()
{
	for(int i=1;i<=n;i++)
	{
		for(int k=0;k<=n;k++)
			ans[i][1][k]=v[i];
	}
	for(int i1=n;i1>=1;i1--)
	{
		
		Node* node=nodes[i1];
		int i=node->index;
//		printf("mark2 %d %d\n",i,node->degree);
		if(node->degree==0)
				continue;	
//		for(int j=0;j<node->degree;j++)
//			printf("%d",node->sons[j]->index);
//			printf("\n");				
		for(int j=2;j<=m;j++)
		{			
	//		printf("mark3 %d\n",j);
			int lastson=node->sons[node->degree-1]->index;
	//		printf("%d\n",lastson);
			ans[i][j][1]=ans[lastson][j-1][rawnodes[lastson].degree]+v[i];
			for(int k=2;k<=node->degree;k++)
			{
			//	printf("mark4 %d\n",k);
				int firstson=node->sons[0-k+node->degree]->index;				
				for(int l=0;l<=j-1;l++)
				{
					if(ans[firstson][l][rawnodes[firstson].degree]+ans[i][j-l][k-1]>ans[i][j][k])
						ans[i][j][k]=ans[firstson][l][rawnodes[firstson].degree]+ans[i][j-l][k-1];
				}
			}
		}
	}
}

void BFS()
{
	int num=1;
	int used[105]={0};
	queue<int> q;
	q.push(1);
	used[1]=1;
	while(!q.empty())
	{
		int c=q.front();
		q.pop();
		nodes[num]=rawnodes+c;
		num++;
		Node *node=rawnodes+c;
		for(int i=1;i<=n;i++)
		{
			if(!used[i]&&edge[c][i])
			{
				q.push(i);
				used[i]=1;
				node->sons[node->degree]=rawnodes+i;
				node->degree++;
			}
		}
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",v+i);
	}
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		edge[a][b]=edge[b][a]=1;
	}


	for(int i=1;i<=n;i++)
	{
		rawnodes[i].index=i;
	}
	BFS();
	//printf("mark\n");
	dp();
	int res=ans[1][m][rawnodes[1].degree];
	printf("%d\n",res);	
	//printf("%d\n",ans[1][4][2]);
	//printf("%d\n",ans[1][4][3]);
	return 0;
}