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
	vector<bool> visited;
	vector<int> parent;
	int n, cycleNode;

	graph(int _n) : n(_n) { nodes.resize(n); visited.resize(n, 0); parent.resize(n, -1); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	bool cycle_dfs(int u, vector<int> &color) {
		color[u] = 1;
		for (auto &x : nodes[u].edges) {
			int v = x.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; cycleNode = v; return true; }
		}
		color[u] = 2; return false;
	}
	int find_cycle() {
		vector<int> color(n, 0);
		for (int v = 0; v < n; v++) {
			if (color[v]) { continue; }
			if (cycle_dfs(v, color)) { return cycleNode; }
		}
		return -1;
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

	int d = g.find_cycle();

	if (d == -1) { cout << "IMPOSSIBLE\n"; }
	else {
		vector<int> ans; ans.push_back(d);
		int cur = g.parent[d];
		while (cur != d) {
			ans.push_back(cur);
			cur = g.parent[cur];
		}
		ans.push_back(cur);
		reverse(ans.begin(), ans.end());

		cout << ans.size() << '\n';
		for (auto &x : ans) { cout << x + 1 << ' '; }
		cout << '\n';
	}
}