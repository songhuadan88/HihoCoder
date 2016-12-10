// Wrong Answer

#include <iostream>
#include <queue>
using namespace std;

struct Node
{
	int left,right;
	int price;
};

const int MAXN=10005;

int n,q,price[MAXN];
Node node[MAXN*2];

void Build(int nodeindex)
{
	if(node[nodeindex].left==node[nodeindex].right)
	{
		node[nodeindex].price=price[node[nodeindex].left];
		return ;
	}
	int mid=(node[nodeindex].left+node[nodeindex].right)/2;
	node[2*nodeindex+1].left=node[nodeindex].left;
	node[2*nodeindex+1].right=mid;
	node[2*nodeindex+2].left=mid+1;
	node[2*nodeindex+2].right=node[nodeindex].right;
	Build(2*nodeindex+1);
	Build(2*nodeindex+2);
	node[nodeindex].price=node[2*nodeindex+1].price+node[2*nodeindex+2].price;
}

int Query(int left,int right,int nodeindex)
{
	if(node[nodeindex].left==left&&node[nodeindex].right==right)
	{
		return node[nodeindex].price;
	}
	int mid=(node[nodeindex].left+node[nodeindex].right)/2;
	if(mid>=right)
	{
		return Query(left,right,2*nodeindex+1);
	}
	if(mid+1<=left)
	{
		return Query(left,right,2*nodeindex+2);
	}
	return Query(left,mid,2*nodeindex+1)+Query(mid+1,right,2*nodeindex+2);
}

void Modify(int left,int right, int newprice,int nodeindex)
{
	if(node[nodeindex].left==node[nodeindex].right)
	{
		node[nodeindex].price=newprice;
		return ;
	}
	int mid=(node[nodeindex].left+node[nodeindex].right)/2;	
	if(mid>=right)
	{
		Modify(left,right,newprice,2*nodeindex+1);
	}
	else if(mid+1<=left)
	{
		Modify(left,right,newprice,2*nodeindex+2);
	}
	else
	{
		Modify(left,mid,newprice,2*nodeindex+1);
		Modify(mid+1,right,newprice,2*nodeindex+2);
	}
	node[nodeindex].price=node[2*nodeindex+1].price+node[2*nodeindex+2].price;
}

int main()
{
	cin>>n;
	for (int i = 0; i < n; i++)
	{
		cin>>price[i];
	}
	node[0].left=0;
	node[0].right=n-1;
	Build(0);
	cin>>q;
	for (int i = 0; i < q; i++)
	{
		int type;
		cin>>type;
		if(type==0)
		{
			int l,r;
			cin>>l>>r;
			cout<<Query(l-1,r-1,0)<<endl;
		}
		else
		{
			int l,r,p;
			cin>>l>>r>>p;
			Modify(l-1,r-1,p,0);
		}

	}

	return 0;
}
