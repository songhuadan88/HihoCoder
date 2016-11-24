#include <iostream>
#include <cstdio>
using namespace std;

const int MAXN=10000+5;
const int MAXWEIGHT=10000+5;

int N,Q;
int w[MAXN];

int main()
{
	scanf("%d",&N);
	for(int i=1;i<=N;i++)
	{
		scanf("%d",w+i);
	}
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		if(x==0)
		{
			int ans=MAXWEIGHT;
			for(int j=y;j<=z;j++)
			{
				if(w[j]<ans)
					ans=w[j];
			}
			printf("%d\n",ans);
		}
		else if(x==1)
		{
			w[y]=z;
		}
	}
	return 0;
}