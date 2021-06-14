//https://codeforces.com/contest/543/problem/D
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<ll> dp, ans;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); dp.resize(n, 1); ans.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs1(int u, int p) {
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs1(e.v, u);
			dp[u] *= (dp[e.v] + 1);
			dp[u] %= mod;
		}
	}

	void dfs2(int u, int p) {
		ans[u] = dp[u];
		ll prevValU = dp[u];

		vector<ll> subtreeVal;
		for (auto& e : nodes[u].edges) {
			subtreeVal.push_back(dp[e.v] + 1);
		}
		int m = subtreeVal.size();
		if (!m) { return; }

		vector<ll> subtreePre(m), subtreSuf(m);
		subtreePre[0] = subtreSuf[m - 1] = 1;
		for (int i = 1; i < m; i++) {
			subtreePre[i] = subtreePre[i - 1] * subtreeVal[i - 1]; subtreePre[i] %= mod;
		}
		for (int i = m - 2; i >= 0; i--) {
			subtreSuf[i] = subtreSuf[i + 1] * subtreeVal[i + 1]; subtreSuf[i] %= mod;
		}

		int i = -1;
		for (auto& e : nodes[u].edges) {
			i++;
			if (e.v == p) { continue; }
			ll prevValV = dp[e.v];
			dp[u] = subtreePre[i] * subtreSuf[i]; dp[u] %= mod;
			dp[e.v] *= (dp[u] + 1); dp[e.v] %= mod;
			dfs2(e.v, u);
			dp[u] = prevValU;
			dp[e.v] = prevValV;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 1; i <= n - 1; i++) {
		int p; cin >> p; p--;
		t.add_edge(i, p);
	}

	t.dfs1(0, -1);
	t.dfs2(0, -1);
	for (int i = 0; i < n; i++) {
		cout << t.ans[i] << ' ';
	}
}