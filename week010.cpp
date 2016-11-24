#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

struct node
{
	char c;
	node* left;
	node* right;
	node(){left=right=NULL;}	
};

char rootfirst[30],rootmiddle[30];

node* recover(int index1,int index2,int len)
{
	if(len==0)
		return NULL;
	node* root=new node();
	root->c=rootfirst[index1];
	for(int j=0;j<len;j++)
	{
		if(rootmiddle[j+index2]==rootfirst[index1])
		{
			root->left=recover(index1+1,index2,j);
			root->right=recover(index1+1+j,index2+j+1,len-1-j);
		}
	}
	return root;
}

void rootlast(node* current)
{
	if(current==NULL)
		return ;
	rootlast(current->left);
	rootlast(current->right);
	printf("%c",current->c);
}

int main()
{
	scanf("%s%s",rootfirst,rootmiddle);
	node* root=recover(0,0,strlen(rootfirst));
	rootlast(root);
	printf("\n");
	return 0;
}