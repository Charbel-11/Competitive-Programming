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
	vector<int> color;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); color.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool dfs(int s) {
		stack<int> S; S.push(s); color[s] = 1;

		while (!S.empty()) {
			int cur = S.top(); S.pop();
			for (auto &e : nodes[cur].edges) {
				if (color[e.v] == color[cur]) { return false; }
				if (color[e.v] != -1) { continue; }
				color[e.v] = (color[cur] == 1 ? 2 : 1);
				S.push(e.v);
			}
		}

		return true;
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

	for (int i = 0; i < n; i++) {
		if (g.color[i] != -1) { continue; }
		bool b = g.dfs(i);
		if (!b) { cout << "IMPOSSIBLE\n";  return 0; }
	}

	for (int i = 0; i < n; i++) { cout << g.color[i] << ' '; }
	cout << '\n';
}