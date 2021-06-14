#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
vector<ll> dp;
ll res;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> sz;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); sz.resize(n, 1); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs1(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (p == e.v) { continue; }

			dfs1(e.v, u);
			sz[u] += sz[e.v];
			dp[u] += dp[e.v];
		}

		dp[u] += sz[u];
		res = dp[u];
	}

	void dfs2(int u, int p) {
		res = max(res, dp[u]);

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }

			dp[u] -= (dp[e.v] + sz[e.v]);
			sz[u] -= sz[e.v];
			dp[e.v] += (dp[u] + sz[u]);
			sz[e.v] += sz[u];

			dfs2(e.v, u);

			dp[e.v] -= (dp[u] + sz[u]);
			sz[e.v] -= sz[u];
			dp[u] += (dp[e.v] + sz[e.v]);
			sz[u] += sz[e.v];
		}
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	dp.resize(n, 0);
	t.dfs1(0, -1);
	t.dfs2(0, -1);

	cout << res << endl;
}