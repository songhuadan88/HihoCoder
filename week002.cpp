#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Node
{
	int letter;
	int count;
	Node* sons[26];
	Node(int _letter)
	{
		letter=_letter;
		count=0;
		for (int i = 0; i < 26; ++i)
		{
			sons[i]=NULL;
		}
	}
};

void InsertWord(Node* node,char* word,int len,int index)
{
	if(index==len)
		return ;
	int l=word[index]-'a';
	if(node->sons[l]==NULL)
	{
		node->sons[l]=new Node(l);
	}
	node->sons[l]->count++;

	InsertWord(node->sons[l],word,len,index+1);

}

int QueryWord(Node* node,char* word,int len)
{
	for(int i=0;i<len;i++)
	{
		//cout<<i<<endl;
		int l=word[i]-'a';
		if(node->sons[l]==NULL)
			return 0;
		node=node->sons[l];
	}
	//cout<<"qq"<<node->count<<"ww"<<endl;
	return node->count;
}

int main()
{
	int n,m;
	char word[15];
	Node* head=new  Node(-1);
	scanf("%d",&n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%s",word);
		InsertWord(head,word,strlen(word),0);
	}
	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		scanf("%s",word);
		cout<<QueryWord(head,word,strlen(word))<<endl;
	}

	return 0;
}
