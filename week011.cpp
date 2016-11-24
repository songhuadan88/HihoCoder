#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <memory.h>
using namespace std;

int n;
vector<int> nextvertex[100000+5];

int main()
{
	scanf("%d",&n);
	int v1,v2;
	for(int i=0;i<n-1;i++)
	{
		scanf("%d%d",&v1,&v2);
		nextvertex[v1].push_back(v2);
		nextvertex[v2].push_back(v1);
	}
	//printf("m1\n");
	int searched1[100000+5]={0};
	queue<int> q1;
	q1.push(1);
	searched1[1]=1;
	int last=1;
	while(!q1.empty())
	{
		int c=q1.front();
		q1.pop();
		last=c;
		for(vector<int>::iterator ii=nextvertex[c].begin();ii!=nextvertex[c].end();ii++)
		{
			if(searched1[*ii]==0)
			{
				searched1[*ii]=1;
				q1.push(*ii);
			}
		}
	}
	//printf("m2\n");
	int distance[100000+5]={0};
	memset(distance,-1,sizeof(distance));
	distance[last]=0;
	queue<int> q2;
	q2.push(last);
	while(!q2.empty())
	{
		int c=q2.front();
		q2.pop();		
		for(vector<int>::iterator ii=nextvertex[c].begin();ii!=nextvertex[c].end();ii++)
		{
			if(distance[*ii]<0)
			{
				distance[*ii]=distance[c]+1;
				q2.push(*ii);
			}
		}
	}
 //printf("m3\n");
	int ans=distance[1];
	for(int i=2;i<=n;i++)
	{
		if(distance[i]>ans)
			ans=distance[i];
	}
	printf("%d\n",ans);
	return 0;
}