// WRONG ANSWER

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 1000 + 5;
const int MAXT = 10000 + 5;
const int INF = 1 << 30;

struct Interval
{
	int left, right;
};

bool operator<(Interval i1, Interval i2)
{
	return i1.left < i2.left;
}

struct IntSet
{
	vector<Interval> vec;
	void Combine()
	{
		if (vec.empty())
			return;
		vector<Interval> v(vec);
		vec.clear();
		sort(v.begin(), v.end());
		vector<Interval>::iterator ii = v.begin(), last;
		last = ii;
		++ii;
		for (; ii != v.end(); ++ii)
		{
			if (last->right >= ii->left)
				last->right = max(last->right, ii->right);
			else
			{
				vec.push_back(*last);
				last = ii;
			}
		}
		vec.push_back(*last);
	}
};

IntSet Combine(IntSet is1, IntSet is2)
{
	IntSet ret;
	int sz1 = is1.vec.size(), sz2 = is2.vec.size();
	int index1 = 0, index2 = 0;
	while (index1 < sz1 && index2 < sz2)
	{
		if (is1.vec[index1].right <= is2.vec[index2].left)
			++index1;
		else if (is2.vec[index2].right <= is1.vec[index1].left)
			++index2;
		else
		{
			Interval itv;
			itv.left = max(is1.vec[index1].left, is2.vec[index2].left);
			itv.right = min(is1.vec[index1].right, is2.vec[index2].right);
			ret.vec.push_back(itv);
			if (itv.right == is1.vec[index1].right)
				++index1;
			else
				++index2;
		}
	}
	return ret;
}

int T, L, R, N, Q;
int t[MAXT], l[MAXT], n[MAXT], d[MAXT];
IntSet cannot[MAXN][2],allnot[2];

void AddInt(int k)
{
	Interval itv;
	itv.left = t[k] - L + 1;
	itv.right = t[k] + l[k];
	cannot[n[k]][1 - d[k]].vec.push_back(itv);
	
	if (L == l[k])
	{
		itv.left = t[k];
		itv.right = t[k] + 1;
	}
	else if (L < l[k])
	{
		itv.left = t[k] + 1;
		itv.right = t[k] - L + l[k];
	}
	else
	{
		itv.left = t[k] + l[k] - L + 1;
		itv.right = t[k];
	}
	if (abs(L - l[k]) != 1)
		cannot[n[k]][d[k]].vec.push_back(itv);
}

int AvailTime(IntSet is, int time)
{
	Interval itv;	
	int left = 0, right = is.vec.size()-1;
	while (left < right)
	{
		int mid = (left + right ) / 2;
		if (is.vec[mid].left>time)
			right = mid;
		else if (is.vec[mid].right <= time)
			left = mid + 1;
		else
			return is.vec[mid].right;
	}
	return time;
}

int main()
{
	int TASK;
	cin >> TASK;
	while (TASK--)
	{
		cin >> T >> L >> R >> N >> Q;
		for (int i = 0; i < N; ++i)
		{
			cannot[i][0].vec.clear();
			cannot[i][1].vec.clear();
		}
		for (int k = 0; k < Q; ++k)
		{
			cin >> t[k] >> l[k] >> n[k] >> d[k];
			AddInt(k);
		}
		for (int i = 0; i < N; ++i)
		{
			cannot[i][0].Combine();
			cannot[i][1].Combine();
		}
		allnot[0] = cannot[0][0];
		allnot[1] = cannot[0][1];
		for (int i = 1; i < N; ++i)
		{
			allnot[0] = Combine(allnot[0], cannot[i][0]);
			allnot[1] = Combine(allnot[1], cannot[i][1]);
		}
		
		int dir = 0;
		for (int i = 0; i < R; ++i)
		{
			T = AvailTime(allnot[dir], T);
			T = T + L;
			dir = 1 - dir;
		}
		cout << T << endl;
	}
	return 0;
}
