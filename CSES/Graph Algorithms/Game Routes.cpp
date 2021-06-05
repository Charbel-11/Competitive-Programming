#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1000 * 1000 * 1000 + 7;

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
		edge e1(u, v);
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

	vector<int> order = g.topological_sort();
	vector<ll> dp(n, 0); dp[0] = 1;
	for (int i = 0; i < n; i++) {
		for (auto &e : g.nodes[order[i]].edges) {
			dp[e.v] += dp[e.u]; dp[e.v] %= mod;
		}
	}

	cout << dp[n - 1] << '\n';
}