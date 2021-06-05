#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
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
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void dfs(int u, vector<bool> &visited) {
		stack<int> S; S.push(u); visited[u] = 1;

		while (!S.empty()) {
			int cur = S.top(); S.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				S.push(e.v); visited[e.v] = 1;
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

	vector<bool> visited(n, false);
	vector<pair<int, int>> ans;
	for (int i = 0; i < n; i++) {
		if (visited[i]) { continue; }
		g.dfs(i, visited);
		if (i) { ans.push_back({ 1, i + 1 }); }
	}

	cout << ans.size() << '\n';
	for (auto &p : ans) { cout << p.first << " " << p.second << '\n'; }
}