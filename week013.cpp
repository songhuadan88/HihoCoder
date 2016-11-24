#include <cstdio>
#include <cstring>
using namespace std;

struct node
{
	int index;
	int father;
	int flag;	
};

int n,m;
char name[205][10005]={0};
int namenum=0;
node person[205];
char nnn[10005],nnn1[10005];

int getmainfather(int index1,int index2)
{
	for(int i=0;i<namenum;i++)
	{
		person[i].flag=0;
	}
	while(index1>=0)
	{
		person[index1].flag=1;
		index1=person[index1].father;
	}
	while(index2>=0)
	{
		if(person[index2].flag)
			return index2;
		index2=person[index2].father;
	}
	return -1;
}

int queryindex()
{
	for(int i=0;i<namenum;i++)
	{
		if(strcmp(name[i],nnn)==0)
			return i;
	}
	return -1;
}

int getindex()
{
	int index=queryindex();
	if(index>=0)
		return index;
	strcpy(name[namenum],nnn);
	namenum++;
	return namenum-1;
}

int main()
{
	for(int i=0;i<205;i++)
	{
		person[i].index=i;
		person[i].father=-1;		
	}
	scanf("%d",&n);	
	for(int i=0;i<n;i++)
	{		
		scanf("%s",nnn);
		int index1=getindex();
		scanf("%s",nnn);
		int index2=getindex();
		person[index2].father=index1;
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s",nnn);
		int index1=queryindex();
		scanf("%s",nnn1);
		// two persons are the same, but not mentioned before
		if(strcmp(nnn,nnn1)==0)
		{
			printf("%s\n",nnn);
			continue;
		}
		strcpy(nnn,nnn1);
		int index2=queryindex();
		if(index1<0 || index2<0)
		{
			printf("-1\n");
			continue;
		}
		int fatherindex=getmainfather(index1,index2);
		printf("%s\n",name[fatherindex]);
	}
	return 0;
}