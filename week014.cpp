#include <iostream>
#include <cstdio>
#include <memory.h>
#include <cstring>

using namespace std;
const int MAXN=100005;

char name[2*MAXN][105]={0};
int namecount={0};
char name1[105],name2[105];
int father[2*MAXN]={0};
int n,op;

int query(char* nnn)
{
	for(int i=0;i<namecount;i++)
	{
		if(strcmp(name[i],nnn)==0)
			return i;
	}
	strcpy(name[namecount],nnn);
	namecount++;
	return namecount-1;
}

int queryfather(int index)
{	
//	printf("index=%d\n",index);
	if(father[index]==-1)
		return index;
	int f=queryfather(father[index]);
	father[index]=f;
	return f;
}

int setfather(int index1,int index2)
{
//	printf("MM1\n");
	int f1=queryfather(index1);
//	printf("MM2\n");
	int f2=queryfather(index2);
//	printf("MM3\n");
//	if(index1==3 && index2==4)
//		printf("%d %d\n",f1,f2);
	if(f1!=f2)
		father[f1]=f2;
//	printf("MM4\n");
}

int main()
{
	memset(father,-1,sizeof(father));
	scanf("%d",&n);
	while(n--)
	{
		scanf("%d%s%s",&op,name1,name2);
		int index1=query(name1);
		int index2=query(name2);
		if(op==0)
		{
//			printf("%d %d\n",index1,index2);
			setfather(index1,index2);
//			printf("MM\n");
		}
		else if(op==1)
		{
			int f1=queryfather(index1);
			int f2=queryfather(index2);
			if(f1==f2)
				printf("yes\n");
			else
				printf("no\n");
		}
//		printf("%d\n",n);
	}	
	return 0;
}