#include <cstdio>
using namespace std;

const int MAXN=1000000+5;
const int MAXWEIGHT=10000+5;

int n,q,l,r,ans;
int m[MAXN][25];
int w[MAXN];

inline int min(int m1,int m2)
{
	if(m1<m2)
		return m1;
	return m2;
}

int level(int length)
{
	int n=0;
	while(length>>1)
	{
		n++;
		length=length>>1;
	}
	return n;
}

int main()
{
	scanf("%d",&n);	
	for(int i=1;i<=n;i++)
	{
		scanf("%d",w+i);
		m[i][0]=w[i];
	}
	for(int j=1;j<=20;j++)
	for(int i=1;i<=n;i++)
		
		{
			if(i+(1<<j)-1>n)
				break;
			m[i][j]=min(m[i][j-1],m[i+(1<<(j-1))][j-1]);
		}
	scanf("%d",&q);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&l,&r);
		int h=level(r-l+1);
		ans=min(m[l][h],m[r+1-(1<<h)][h]);
		printf("%d\n",ans);
	}
	return 0;
}
