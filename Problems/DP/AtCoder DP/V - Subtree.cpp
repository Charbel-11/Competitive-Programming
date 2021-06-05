#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
ll mod;
vector<ll> ans;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<ll> dp;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dp.resize(n, 1); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		dp[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			dp[u] *= (dp[e.v] + 1); dp[u] %= mod;
		}
	}

	void reroot(int u, int p) {
		ans[u] = dp[u];
		int m = nodes[u].edges.size();
		vector<ll> pref(m, 1), suf(m + 1, 1);

		for (int i = 0; i < m; i++) {
			pref[i] = (i ? pref[i - 1] : 1) * (dp[nodes[u].edges[i].v] + 1);
			pref[i] %= mod;
		}
		for (int i = m - 1; i >= 0; i--) {
			suf[i] = suf[i + 1] * (dp[nodes[u].edges[i].v] + 1);
			suf[i] %= mod;
		}

		int idx = -1;
		for (auto &e : nodes[u].edges) {
			idx++;
			if (e.v == p) { continue; }

			ll prevU = dp[u], prevV = dp[e.v];
			dp[u] = (idx ? pref[idx - 1] : 1) * suf[idx + 1]; dp[u] %= mod;
			dp[e.v] *= (dp[u] + 1); dp[e.v] %= mod;
			reroot(e.v, u);
			dp[e.v] = prevV;
			dp[u] = prevU;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n >> mod;
	tree t(n); ans.resize(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, -1);
	t.reroot(0, -1);

	for (auto &x : ans) { cout << x << '\n'; }
}