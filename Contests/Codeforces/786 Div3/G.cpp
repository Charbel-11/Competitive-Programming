#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; vector<edge> inEdges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		nodes[v].inEdges.push_back(e1);
	}

	void dfs(int u, vector<int>& visited, vector<int>& ans) {
		visited[u] = true;
		for (auto& e : nodes[u].edges) {
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

	vector<int> dp(n, 1), topOrder = g.topological_sort();
	for (int idx = 0; idx < n; idx++) {
		int curIdx = topOrder[idx];
		auto& curNode = g.nodes[curIdx];
		if (curNode.inEdges.size() <= 1) { continue; }

		for (auto& iE : curNode.inEdges) {
			int prev = iE.u;
			if (g.nodes[prev].edges.size() == 1) { continue; }
			dp[curIdx] = max(dp[curIdx], dp[prev] + 1);
		}
	}

	int ans = *max_element(dp.begin(), dp.end());
	cout << ans << '\n';
}