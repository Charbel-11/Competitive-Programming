#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> dist, parent;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, n + 2); parent.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void bfs(int s) {
		vector<bool> visited(n, 0);
		dist[s] = 1; visited[s] = 1;
		queue<int> Q; Q.push(s);

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				dist[e.v] = dist[cur] + 1;
				parent[e.v] = cur;
				visited[e.v] = 1; Q.push(e.v);
			}
		}
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

	g.bfs(0);
	if (g.dist[n - 1] > n) { cout << "IMPOSSIBLE\n"; }
	else {
		cout << g.dist[n - 1] << '\n';
		vector<int> path;
		int cur = n - 1;
		while (cur != 0) {
			path.push_back(cur); 
			cur = g.parent[cur];
		}
		path.push_back(0);
		reverse(path.begin(), path.end());
		for (auto &x : path) { cout << x + 1 << ' '; }
		cout << '\n';
	}
}