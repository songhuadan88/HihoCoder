#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;

const int MAXN = 50000 + 5;
const int MAXPOINTINREGION = 10;

struct Point
{
	int x, y;
	Point(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	};
};

struct Region // shape of Region is Square
{
	Point center;
	int radium; // radium is the half of the length of edges
	Region* son[4];
	bool divided;
	vector<Point> point;

	Region()
	{
		memset(son, 0, sizeof(son));
		divided = false;
		point.clear();
	}

	bool contain(Point point)
	{
		if (abs(point.x - center.x) > radium)
			return false;
		if (abs(point.y - center.y) > radium)
			return false;
		return true;
	}

	void insert(Point p)
	{
		if (divided)
		{
			for (int i = 0; i < 4; i++)
			{
				// because the son regions have intersect, the point should be inserted into only one son region
				if (son[i]->contain(p))
				{
					son[i]->insert(p);
					return;
				}
			}
		}
		point.push_back(p);
		trydivide();
	}

	void trydivide()
	{
		if (point.size() < MAXPOINTINREGION)
			return;
		divided = true;
		int changex, changey, newradium; // son region's radium is newradium, center is (center.x+=changex,center.y+=changey)
		if (radium % 2 == 0)
		{
			changex = changey = radium / 2;
			newradium = radium / 2;
		}
		else
		{
			changex = changey = (radium - 1) / 2;
			newradium = (radium + 1) / 2;
		}
		int dx[] = { -1, -1, 1, 1 };
		int dy[] = { -1, 1, -1, 1 };
		for (int i = 0; i < 4; ++i)
		{
			son[i] = new Region();
			son[i]->center = Point(center.x + dx[i] * changex, center.y + dy[i] * changey);
			son[i]->radium = newradium;
		}
		for (vector<Point>::iterator ii = point.begin(); ii != point.end(); ++ii)
		{
			for (int i = 0; i < 4; ++i)
			{
				if (son[i]->contain(*ii))
				{
					son[i]->insert(*ii);
					break;
				}
			}
		}
		point.clear(); // put all the points into the son region
		for (int i = 0; i < 4; ++i)
		{
			son[i]->trydivide(); 
		}//in case that all points are in one son region, try divide for son regions
	}

	int query(Point p, int r)
	{
		if (!divided)
		{
			// range over all the points
			int ret = 0;
			for (vector<Point>::iterator ii = point.begin(); ii != point.end(); ++ii)
			{
				int dx = p.x - ii->x;
				int dy = p.y - ii->y;
				if (dx*dx + dy*dy <= r*r)
					ret++;
			}
			return ret;
		}
		// if no intersect, then directly return 0
		if (abs(center.x - p.x) > radium + r)
			return 0;
		if (abs(center.y - p.y) > radium + r)
			return 0;
		// if has intersect, then add the result for all four son regions
		int ret = 0;
		for (int i = 0; i < 4; ++i)
		{
			ret += son[i]->query(p, r);
		}
		return ret;
	}
};

int n, m;
Region root;

int main()
{
	root.center = Point(15000, 15000);
	root.radium = 15000;
	cin >> n >> m;
	while (n--)
	{
		Point p;
		cin >> p.x>>p.y;
		root.insert( p);
	}
	while (m--)
	{
		int a, b, r;
		cin >> a >> b >> r;
		cout << root.query(Point(a,b), r) << endl;
	}

	return 0;
}
