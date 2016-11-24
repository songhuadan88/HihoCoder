#include <iostream>
#include <cstdio>
using namespace std;

int n,m;
const int MAXP=1000000007;
int dp1[1005][40]={0};
int dp2[1005][40]={0};
int legal[40][40]={0};
int d[]={3,6,12,24};

int canadd(int n1,int n2)
{

	for(int i=0;i<m;i++)
	{
		if((n1&(1<<i))>0)
			if((n2&(1<<i))>0)
				return 0;
	}

	return 1;
}

void calclegal()
{
	for(int i=0;i<(1<<m);i++)
	{
		legal[i][i]=1;		
		int flag=1;
		while(flag)
		{
			flag=0;
			for(int j=0;j<(1<<m);j++)
				if(legal[i][j]==1)
					for(int k=0;k<m-1;k++)
					{
						if(j+d[k]<(1<<m) && canadd(j,d[k]) && legal[i][j+d[k]]==0)
						{
							legal[i][j+d[k]]=1;
							flag=1;							
						}
					}
		}
	}
}

void showlegal()
{
	for(int i=0;i<(1<<m);i++)
	{
		printf("%d: ",i);
		for(int j=0;j<(1<<m);j++)
		{
			if(legal[i][j]==1)
			printf("%d ",j);

		}
		printf("\n");
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	calclegal();
	//showlegal();

	for(int j=0;j<(1<<m);j++)
	{
		if(legal[j][(1<<m)-1])
			dp1[0][j]=1;
	}
	for(int j=0;j<(1<<m);j++)
	{
		for(int k=0;k<(1<<m);k++)
		{
			if(legal[j][k])
			{
				dp2[0][k]+=dp1[0][j];
			}
		}
	}
	for(int i=1;i<n-1;i++)
	{
		for(int j=0;j<(1<<m);j++)
		{
			dp1[i][j]=dp2[i-1][(1<<m)-1-j];
		}
		for(int j=0;j<(1<<m);j++)
		{
			for(int k=0;k<(1<<m);k++)
			{
				if(legal[j][k])
				{
					dp2[i][k]=(dp2[i][k]+dp1[i][j])%MAXP;
				}
			}
		}
	}
	printf("%d\n",dp2[n-2][(1<<m)-1]);
	return 0;
}