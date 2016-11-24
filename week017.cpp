#include <cstdio>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstring>
#include <iostream>
using namespace std;

const int MAXN=100000+5;
struct Node
{
	int index;
	int parent;
	vector<int> children;
	int level;
	int position;
	string name;
	Node()
	{
		children.clear();
	}
};
struct LittleNode
{
	int index;
	int level;
};

int n,m;
map<string,int> allnames;
char name1[100],name2[100];
Node nodes[MAXN];
LittleNode lnodes[MAXN*2];
int count=0;
int leastlevel[MAXN*2][25];

int calcleastlevel(int index1,int index2)
{
	//printf("%d %d\n",index1,index2);
	int pos;
	int p1=nodes[index1].position;
	int p2=nodes[index2].position;
	//printf("%d %d\n",p1,p2);
	if(p1>p2)
	{
		p1=p1+p2;
		p2=p1-p2;
		p1=p1-p2;
	}
	int num=p2-p1+1;
	int power=0;
	while(num>>1)
	{
		power++;
		num=num>>1;
	}	
	//printf("%d %d %d\n",p1,p2,power);
	int lp1=leastlevel[p1][power];
	int lp2=leastlevel[p2-(1<<power)+1][power];
	//printf("%d %d %d\n",lp1,lp2,power);
	if(lnodes[lp1].level<lnodes[lp2].level)
		return lp1;
	return lp2;
}

void preleastlevel()
{
	//printf("leastlevel[5][0]: %d\n",leastlevel[5][0]);
	//printf("n: %d\n",n);
	for(int i=0;i<count;i++)
	{
		leastlevel[i][0]=i;
	}
	//printf("leastlevel[5][0]: %d\n",leastlevel[5][0]);
	for(int j=1;j<25;j++)
	{
		for(int i=0;i<count;i++)
		{
			if(i+(1<<j)-1>=count)
				break;
			int p1=leastlevel[i][j-1];
			int p2=leastlevel[i+(1<<(j-1))][j-1];
			if(lnodes[p1].level<lnodes[p2].level)
				leastlevel[i][j]=p1;
			else
				leastlevel[i][j]=p2;
		}
	}
	//printf("leastlevel[5][0]: %d\n",leastlevel[5][0]);
}

void calcposition()
{
	for(int i=0;i<count;i++)
	{
		nodes[lnodes[i].index].position=i;
	}
}

int query(char* name)
{
	string str(name);
	map<string,int>::iterator ii=allnames.find(str);
	if(ii!=allnames.end())
	{
		return ii->second;
	}
	int sz=allnames.size();
	allnames.insert(pair<string,int>(str,sz));
	return sz;
}

void calclevel()
{
	nodes[0].level=0;
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int c=q.front();
		q.pop();
		for(vector<int>::iterator ii=nodes[c].children.begin();ii!=nodes[c].children.end();ii++)
		{
			nodes[*ii].level=nodes[c].level+1;
			q.push(*ii);
		}
	}
}

void dfs(int iii)
{	
	lnodes[count].index=nodes[iii].index;
	lnodes[count].level=nodes[iii].level;
	count++;
	for(vector<int>::iterator ii=nodes[iii].children.begin();ii!=nodes[iii].children.end();ii++)
	{
		dfs(*ii);
		lnodes[count].index=nodes[iii].index;
		lnodes[count].level=nodes[iii].level;
		count++;			
	}	
}

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%s%s",name1,name2);
		int index1=query(name1);
		int index2=query(name2);
		nodes[index2].parent=index1;
		nodes[index1].children.push_back(index2);
	}
	for(map<string,int>::iterator ii=allnames.begin();ii!=allnames.end();ii++)
	{
		nodes[ii->second].index=ii->second;
		nodes[ii->second].name=ii->first;
	}
	calclevel();
	dfs(0);
/*	printf("%d\n",count);
	for(int i=0;i<count;i++)
	{
		printf("%d %d %d\n",i,lnodes[i].index,lnodes[i].level);
	} */
	calcposition();
	preleastlevel();
	//printf("leastlevel[3][1]: %d\n",leastlevel[3][1]);
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s%s",name1,name2);
		int index1=query(name1);
		int index2=query(name2);
		int pos=calcleastlevel(index1,index2);
		//printf("ret pos: %d\n",pos);
		printf("%s\n",nodes[lnodes[pos].index].name.c_str());
	}
	return 0;
}