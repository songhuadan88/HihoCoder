#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>

using namespace std;
struct Node
{
	bool mark;
	Node* father;
	Node* children[26];
	Node* next;
	int index;

	Node()
	{
		mark=false;
		father=NULL;
		for(int i=0;i<26;i++)
			children[i]=NULL;
		index=-1;
		next=NULL;
	}
	void SetChildren(int index,Node* node)
	{
		children[index]=node;
		node->father=this;
	}
};
Node* root;
char str[1000005];

void InsertWord()
{
	int len=strlen(str);
	Node* current=root;
	for(int i=0;i<len;i++)
	{
		int index=str[i]-'a';
		if(current->children[index]==NULL)
		{
			Node* temp=new  Node();
			temp->index=index;
			current->SetChildren(index,temp);
		}
		current=current->children[index];
	}
	current->mark=true;
}

void GetNext()
{
	queue<Node*> q;
	for(int i=0;i<26;i++)
	{
		if(root->children[i]!=NULL)
		{
			q.push(root->children[i]);
		}
		else
		{
			root->children[i]=root;
		}
	}
	root->next=root;
	while(!q.empty())
	{
		Node* current=q.front();
		q.pop();
		Node* next=current->father->next->children[current->index];
		if(current->father==root)
			next=root;
		current->next=next;
		if(next->mark)
			current->mark=true;
		for(int i=0;i<26;i++)
		{
			if(current->children[i]!=NULL)
			{
				q.push(current->children[i]);
			}
			else
			{
				current->children[i]=next->children[i];
			}
		}
	}
}

bool Query()
{
	int len=strlen(str);
	Node* current=root;
	for(int i=0;i<len;i++)
	{
		current=current->children[str[i]-'a'];
		if(current->mark)
		{
			//printf("%d\n",i);
			return true;
		}		
	}
	return false;
}

int main()
{
	int n;
	scanf("%d",&n);
	root=new Node();

	for(int i=0;i<n;i++)
	{
		scanf("%s",str);
		InsertWord();
	}
	GetNext();
	scanf("%s",str);
	bool ans=Query();
	if(ans)
	{
		printf("YES\n");
	}
	else
	{
		printf("NO\n");
	}
	return 0;
}