// Accepted Dec. 11, 2016

#include <iostream>
using namespace std;

struct Node
{
	int left, right;
	int totalprice;
	int lazytag; // 1 means that the sons of this node are not up-to-dated
};

const int MAXN = 100000 + 5;

int n, q, price[MAXN];
Node node[MAXN * 4];

void Build(int nodeindex)
{
	if (node[nodeindex].left == node[nodeindex].right)
	{
		node[nodeindex].totalprice = price[node[nodeindex].left];
		node[nodeindex].lazytag = 0;
		return;
	}
	int mid = (node[nodeindex].left + node[nodeindex].right) / 2;
	node[2 * nodeindex + 1].left = node[nodeindex].left;
	node[2 * nodeindex + 1].right = mid;
	node[2 * nodeindex + 2].left = mid + 1;
	node[2 * nodeindex + 2].right = node[nodeindex].right;
	Build(2 * nodeindex + 1);
	Build(2 * nodeindex + 2);
	node[nodeindex].totalprice = node[2 * nodeindex + 1].totalprice + node[2 * nodeindex + 2].totalprice;
	node[nodeindex].lazytag = 0;
}

void EraseTag(int nodeindex)
{
	// erase the lazy tag for this node and pass it onto the sons
	node[nodeindex].lazytag = 0;
	if (node[nodeindex].left == node[nodeindex].right)
		return;
	int averageprice = node[nodeindex].totalprice / (node[nodeindex].right - node[nodeindex].left + 1);
	int mid = (node[nodeindex].left + node[nodeindex].right) / 2;
	node[2 * nodeindex + 1].totalprice = averageprice*(mid - node[nodeindex].left + 1);
	node[2 * nodeindex + 1].lazytag = 1;
	node[2 * nodeindex + 2].totalprice = averageprice*(node[nodeindex].right - mid);
	node[2 * nodeindex + 2].lazytag = 1;
}

int Query(int left, int right, int nodeindex)
{
	if (node[nodeindex].left == left && node[nodeindex].right == right)
	{
		return node[nodeindex].totalprice;
	}
	// if this node is lazy, then erase the tag before accessing its sons
	if (node[nodeindex].lazytag)
	{
		EraseTag(nodeindex);
	}
	int mid = (node[nodeindex].left + node[nodeindex].right) / 2;
	if (mid >= right)
	{
		return Query(left, right, 2 * nodeindex + 1);
	}
	if (mid + 1 <= left)
	{
		return Query(left, right, 2 * nodeindex + 2);
	}
	return Query(left, mid, 2 * nodeindex + 1) + Query(mid + 1, right, 2 * nodeindex + 2);
}

void Modify(int left, int right, int newprice, int nodeindex)
{
	if (node[nodeindex].left == left && node[nodeindex].right == right)
	{
		node[nodeindex].totalprice = newprice * (right-left +1);
		node[nodeindex].lazytag = 1;
		return;
	}
	// if this node is lazy, then erase the tag before accessing its sons
	if (node[nodeindex].lazytag)
	{
		EraseTag(nodeindex);
	}
	int mid = (node[nodeindex].left + node[nodeindex].right) / 2;
	if (mid >= right)
	{
		Modify(left, right, newprice, 2 * nodeindex + 1);
	}
	else if (mid + 1 <= left)
	{
		Modify(left, right, newprice, 2 * nodeindex + 2);
	}
	else
	{
		Modify(left, mid, newprice, 2 * nodeindex + 1);
		Modify(mid + 1, right, newprice, 2 * nodeindex + 2);
	}
	node[nodeindex].totalprice = node[2 * nodeindex + 1].totalprice + node[2 * nodeindex + 2].totalprice;
}

int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> price[i];
	}
	node[0].left = 0;
	node[0].right = n - 1;
	Build(0);
	cin >> q;
	for (int i = 0; i < q; i++)
	{
		int type;
		cin >> type;
		if (type == 0)
		{
			int l, r;
			cin >> l >> r;
			cout << Query(l - 1, r - 1, 0) << endl;
		}
		else
		{
			int l, r, p;
			cin >> l >> r >> p;
			Modify(l - 1, r - 1, p, 0);
		}

	}

	return 0;
}
