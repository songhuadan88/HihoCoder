#include <cstdio>
#include <cstring>
using namespace std;

char pattern[10005],target[1000005];
int lenpattern,lentarget;
int next[10005];

void FillNext()
{
	next[0]=-1;
	next[1]=0;
	int k=0;
	for(int i=2;i<=lenpattern;i++)
	{		
		//printf("%d %d\n",i,k);
		while(k!=-1 && pattern[i-1]!=pattern[k])
			k=next[k];
		if(k==-1)
			next[i]=0;
		else
		{
			next[i]=k+1;			
		}
		k++;
	}
/*	for(int i=0;i<=lenpattern;i++)
		printf("%d ",next[i]);
	printf("\n");
	*/
}

int Match()
{
	int ans=0;
	int i=0,j=0;
	while(i<lentarget)
	{
		//printf("%d %d %d\n",i,j,ans);
		if(j==lenpattern)
		{
			ans++;			
			j=next[j];
			continue;
		}
		if(target[i]==pattern[j])
		{
			i++;
			j++;
			continue;
		}
		while(j!=-1&&target[i]!=pattern[j])
			j=next[j];
		if(j==-1)
		{
			i++;
			j=0;
		}
		else
		{
			i++;
			j++;
		}
	}
	if(j==lenpattern)
		++ans;
	return ans;
}

int main()
{
	int N;
	scanf("%d",&N);
	while(N--)
	{
		scanf("%s%s",pattern,target);
		lenpattern=strlen(pattern);
		lentarget=strlen(target);
		FillNext();
		printf("%d\n",Match());
	}


	return 0;

}