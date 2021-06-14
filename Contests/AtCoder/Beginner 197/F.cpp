#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <climits>
using namespace std;

struct edge {
	int u, v; char c; edge() {}
	edge(int _u, int _v, char _c) :
		u(_u), v(_v), c(_c) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, char c) {
		edge e1(u, v, c), e2(v, u, c);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
};

vector<int> bfs(int u, graph& g) {
	queue<int> q; q.push(u);
	vector<bool> vis(g.n, 0); vis[u] = true;
	vector<int> dist(g.n, INT_MAX / 2); dist[u] = 0;

	while (!q.empty()) {
		int f = q.front(); q.pop();
		node& n = g.nodes[f];
		for (auto& x : n.edges) {
			int dest = x.v;
			if (vis[dest] == false) {
				q.push(dest); vis[dest] = true;
				dist[dest] = dist[f] + 1;
			}
		}
	}

	return move(dist);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	vector<vector<bool>> adj(n, vector<bool>(n, 0));
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		char c; cin >> c;
		adj[u][v] = adj[v][u] = 1;
		g.add_edge(u, v, c);
	}

	graph g2(n * n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cur = i * n + j;

			for (auto& x : g.nodes[i].edges) {
				for (auto& y : g.nodes[j].edges) {
					if (x.c != y.c) { continue; }
					g2.add_edge(cur, x.v * n + y.v, 'a');
				}
			}
		}
	}

	int src = n - 1;
	vector<int> dist = bfs(src, g2);

	int ans = INT_MAX;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int cur = i * n + j;
			if (i == j && dist[cur] < INT_MAX / 2) { ans = min(ans, dist[cur] * 2); }
			else if (adj[i][j]) { ans = min(ans, dist[cur] * 2 + 1); }
		}
	}

	if (ans == INT_MAX) { ans = -1; }
	cout << ans << '\n';
}