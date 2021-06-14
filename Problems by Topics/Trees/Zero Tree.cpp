#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
vector<ll> val, dp;
vector<pair<ll, ll>> change;

struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		ll maxN = 0, maxP = 0;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);

			maxP = max(change[e.v].first, maxP);
			maxN = min(change[e.v].second, maxN);
		}
		val[u] += maxP + maxN;

		if (val[u] > 0) {
			change[u] = { maxP, maxN - val[u] };
		}
		else {
			change[u] = { maxP - val[u], maxN };
		}

		dp[u] = maxP - maxN + abs(val[u]);
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	val.resize(n); dp.resize(n, 0);
	change.resize(n);
	for (auto &x : val) { cin >> x; }
	t.dfs(0, -1);
	cout << dp[0] << endl;
}