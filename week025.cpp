#include <iostream>
#include <queue>
#include <vector>

using namespace std;

const int MAXN = 100000 + 5;
const int MAXM = 1000000 + 5;
const int INF = 1 << 30;

struct Edge
{
	int from, to, length;
};

int n, m, s, t;
vector<Edge> edge[MAXN];
int dist[MAXN];

int main()
{
	cin >> n >> m >> s >> t;
	for (int i = 1; i <= n; ++i)
	{
		edge[i].clear();
		dist[i] = INF;
	}
	for (int k = 0; k < m; ++k)
	{
		int u, v, l;
		cin >> u >> v >> l;
		Edge e;
		e.from = u;
		e.to = v;
		e.length = l;
		edge[u].push_back(e);
		e.from = v;
		e.to = u;
		edge[v].push_back(e);
	}
	dist[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty())
	{
		int c = q.front();
		q.pop();
		for (vector<Edge>::iterator ii = edge[c].begin(); ii != edge[c].end(); ++ii)
		{
			if (dist[c] + ii->length < dist[ii->to])
			{
				dist[ii->to] = dist[c] + ii->length;
				q.push(ii->to);
			}
		}
	}
	cout << dist[t] << endl;
	return 0;
}