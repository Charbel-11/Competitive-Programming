#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
using namespace std;

set<int> ans;

struct edge {
	int u, v, w; edge() {}
	edge(int _u, int _v, int _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w = 0) {
		nodes[u].edges.emplace_back(edges.size());
		edges.emplace_back(u, v, w);
		nodes[v].edges.emplace_back(edges.size());
		edges.emplace_back(v, u, w);
	}

	void artPointDFS(int cur, int p, vector<bool>& vis, vector<int>& low, vector<int>& tin, int& timer) {
		vis[cur] = true; tin[cur] = low[cur] = timer++; int c = 0;
		for (auto& x : nodes[cur].edges) {
			edge& e = edges[x];	if (e.v == p) { continue; }
			if (vis[e.v]) { low[cur] = min(low[cur], tin[e.v]); continue; }

			artPointDFS(e.v, cur, vis, low, tin, timer);
			low[cur] = min(low[cur], low[e.v]); c++;
			if (p != -1 && low[e.v] >= tin[cur]) { ans.insert(cur); }
		}
		if (p == -1 && c > 1) { ans.insert(cur); }
	}

	void findArtPoints() {
		int timer = 0; vector<bool> vis(n, false);
		vector<int> low(n, -1), tin(n, -1);
		for (int i = 0; i < n; i++)	if (!vis[i])
			artPointDFS(i, -1, vis, low, tin, timer);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	g.findArtPoints();
	cout << ans.size() << '\n';
	for (auto& x : ans) { cout << x + 1 << ' '; }
	cout << '\n';
}