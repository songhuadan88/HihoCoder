#include <cstdio>
#include <cmath>

using namespace std;
const int MAXN=105;

int n;
int num[MAXN][MAXN];
int sum[MAXN][MAXN];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=i;j++)
			scanf("%d",&num[i][j]);
	}
	sum[1][1]=num[1][1];
	for(int i=2;i<=n;i++)
	{
		sum[i][1]=sum[i-1][1]+num[i][1];
		for(int j=2;j<i;j++)
		{
			if(sum[i-1][j]>sum[i-1][j-1])
				sum[i][j]=sum[i-1][j];
			else
				sum[i][j]=sum[i-1][j-1];
			sum[i][j]+=num[i][j];
		}
		sum[i][i]=sum[i-1][i-1]+num[i][i];
	}
	int ans=sum[n][1];
	for(int j=1;j<=n;j++)
		if(sum[n][j]>ans)
			ans=sum[n][j];		
	printf("%d\n",ans);
	return 0;
}