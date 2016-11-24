#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

int n,m,q;
int w[1005];
int dp[1005][1105]={0};
int count[1105]={0};

void fillcount()
{
	count[0]=0;
	for(int i=0;i<511;i++)
	{
		count[2*i]=count[i];
		count[2*i+1]=count[i]+1;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",w+i);
	}
	fillcount();
	dp[1][0]=0;
	dp[1][1]=w[1];
	for(int i=2;i<=m;i++)
	{
		if(i>n)
			break;
		for(int j=0;j<(1<<i);j++)
		{
			dp[i][j]=dp[i-1][j/2];
			if(j%2==1)
				dp[i][j]+=w[i];
			if(count[j]>q)
				dp[i][j]=0;
		}
	}
	for(int i=m+1;i<=n;i++)
	{
		for(int j=0;j<(1<<m);j++)
		{
			dp[i][j]=max(dp[i-1][j/2],dp[i-1][j/2+(1<<(m-1))]);
			if(j%2==1)
				dp[i][j]+=w[i];
			if(count[j]>q)
				dp[i][j]=0;
		}
	}
	int ans=dp[n][0];
	for(int j=1;j<(1<<m);j++)
		ans=max(ans,dp[n][j]);
	printf("%d\n",ans);
	return 0;
}