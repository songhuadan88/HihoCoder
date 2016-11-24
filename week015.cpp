#include <iostream>
#include <cstdio>
#include <memory.h>
#include <cstring>
#include <vector>
#include <map>

using namespace std;
const int MAXN=100005;

struct Node
{
	int color;
	int index;
	int father;
	int grayfather;
	vector<int> children;
	vector<int> queries;
};

map<string,int> names;
char name1[105],name2[105];
int n,m;
Node nodes[2*MAXN];
int query1[MAXN],query2[MAXN],ans[MAXN],met[MAXN];
string allnames[MAXN];

int queryindex(char* nnn)
{
	string str(nnn);
	map<string,int>::iterator ii=names.find(str);
	if(ii!=names.end())
		return ii->second;
	names.insert(pair<string,int>(str,names.size()));
	return names.size()-1;
}

int getgrayfather(int index)
{
	int gf=nodes[index].grayfather;
	if(nodes[gf].color==1)
	{
		return gf;
	}
	gf=getgrayfather(gf);
	nodes[index].grayfather=gf;
	return gf;
}

void dfs(int index)
{	
	nodes[index].color=1;
	for(vector<int>::iterator ii=nodes[index].queries.begin();ii!=nodes[index].queries.end();ii++)
	{
		met[*ii]++;
		//printf("MM1 %d %d %d\n",index,*ii,met[*ii]);
		if(met[*ii]==2)
		{
			int anotherindex=query1[*ii]+query2[*ii]-index;
			int anothercolor=nodes[anotherindex].color;
			//printf("MM2 %d %d\n",*ii,anothercolor);
			if(anothercolor==1)
				ans[*ii]=anotherindex;
			else if(anothercolor==2)
			{
				ans[*ii]=getgrayfather(anotherindex);
			}
		}
	}
	for(vector<int>::iterator ii=nodes[index].children.begin();ii!=nodes[index].children.end();ii++)
	{
		dfs(*ii);
		nodes[*ii].grayfather=index;
	}
	nodes[index].color=2;	
}

int main()
{
	for(int i=0;i<2*MAXN;i++)
	{
		nodes[i].index=i;	
		nodes[i].color=0;
		nodes[i].father=-1;
		nodes[i].grayfather=-1;
	}
	scanf("%d",&n);
	while(n--)
	{
		scanf("%s%s",name1,name2);
		int index1=queryindex(name1);
		int index2=queryindex(name2);
		nodes[index1].children.push_back(index2);
		nodes[index2].father=index1;
	}	
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s%s",name1,name2);
		met[i]=0;
		query1[i]=queryindex(name1);
		query2[i]=queryindex(name2);
		if(query1[i]==query2[i])
		{
			ans[i]=query1[i];
			continue;
		}
		nodes[query1[i]].queries.push_back(i);
		nodes[query2[i]].queries.push_back(i);	
	}
	dfs(0);
	
	for(map<string,int>::iterator ii=names.begin();ii!=names.end();ii++)
	{
		allnames[ii->second]=ii->first;
	}

	for(int i=0;i<m;i++)
	{
		printf("%s\n",allnames[ans[i]].c_str());
	
	}
	return 0;
}
