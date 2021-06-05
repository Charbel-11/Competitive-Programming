#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>
#include <queue>
#include <climits>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<bool> visited;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); visited.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void dfs(int u) {
		if (visited[u]) { return; }
		visited[u] = 1;
		for (auto &e : nodes[u].edges) { dfs(e.v); }
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n*m);
	vector<string> grid(n); for (auto &x : grid) { cin >> x; }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#') { continue; }
			if (i < n - 1 && grid[i+1][j] != '#') { g.add_edge(i*m + j, (i + 1)*m + j); }
			if (j < m - 1 && grid[i][j+1] != '#') { g.add_edge(i*m + j, i*m + j + 1); }
		}
	}

	int res = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == '#') { continue; }
			int cur = i * m + j;
			if (g.visited[cur]) { continue; }
			res++; g.dfs(cur);
		}
	}

	cout << res << '\n';
}