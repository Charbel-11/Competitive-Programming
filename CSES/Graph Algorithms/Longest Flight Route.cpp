#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w = 0) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
	}

	void dfs(int u, vector<int> &visited, vector<int> &ans) {
		visited[u] = true;
		for (auto &e : nodes[u].edges) {
			int v = e.v;
			if (!visited[v]) { dfs(v, visited, ans); }
		}
		ans.push_back(u);
	}
	vector<int> topological_sort() {
		vector<int> visited(n, false), ans;
		for (int i = 0; i < n; ++i)
			if (!visited[i]) { dfs(i, visited, ans); }
		reverse(ans.begin(), ans.end());
		return move(ans);
	}

	vector<int> longestPath() {
		vector<int> DP(n, 0), topSort = topological_sort();
		vector<int> parent(n, -1), start(n, -1); start[0] = 0;

		int st = 0;
		for (int i = 0; i < n; i++) {
			if (topSort[i] == 0) { st = i; break; }
		}

		for (int i = st; i < n; i++) {
			for (auto &e : nodes[topSort[i]].edges) {
				if (DP[e.u] + 1 > DP[e.v]) {
					DP[e.v] = DP[e.u] + 1;
					start[e.v] = start[e.u];
					if (start[e.u] == 0) { parent[e.v] = e.u; }
				}
			}
		}

		vector<int> ans; int cur = n-1;
		while (cur != -1) { ans.push_back(cur);	cur = parent[cur]; }

		reverse(ans.begin(), ans.end());
		return move(ans);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<int> ans = g.longestPath();
	if (ans.size() < 2) { cout << "IMPOSSIBLE\n"; return 0; }
	cout << ans.size() << '\n';
	for (auto &x : ans) { cout << x + 1 << ' '; }
	cout << '\n';
}