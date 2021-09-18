#include <iostream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
using namespace std;

vector<bitset<50000>> dp;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
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
	graph g(n); dp.resize(n, bitset<50000>(0));
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<int> topSort = g.topological_sort();
	reverse(topSort.begin(), topSort.end());

	for (auto u : topSort) {
		dp[u][u] = 1;
		for (auto& e : g.nodes[u].edges) {
			dp[u] |= dp[e.v];
		}
	}

	for (int i = 0; i < n; i++) {
		cout << dp[i].count() << ' ';
	}
}