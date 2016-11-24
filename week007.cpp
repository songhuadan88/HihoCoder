#include <cstdio>
using namespace std;

const int MAXN=505,MAXM=100005;
int n,m;
int ans[MAXN][MAXM];
int weight[MAXN],value[MAXN];

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
	{
		scanf("%d%d",weight+i,value+i);
	}
	for(int j=0;j<=m;j++)
	{
		ans[0][j]=j/weight[0]*value[0];
	}
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<=m;j++)
		{
			ans[i][j]=ans[i-1][j];
			if(j>=weight[i])
			{
				if(ans[i][j-weight[i]]+value[i]>ans[i][j])
					ans[i][j]=ans[i][j-weight[i]]+value[i];
			}
		}
	}
	printf("%d\n",ans[n-1][m]);
	return 0;
}