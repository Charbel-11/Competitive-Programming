#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <cstring>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;
const ll INF = 1e17;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

ll dp[(int)1e5 + 2][2];

//Everything is 0-indexed
struct tree {
	vector<node> nodes;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
	 
	//DP is needed here since we can get to the same substate in a lot of cases
	ll ways(int cur, int p, bool b) {
		if (dp[cur][b] != -1) { return dp[cur][b]; }
		ll ans = 1;

		for (auto &e : nodes[cur].edges) {
			if (e.v == p) { continue; }
			ll w = ways(e.v, cur, 0);
			if (!b) { w += ways(e.v, cur, 1); w %= mod; }
			ans *= w; ans %= mod;
		}

		return dp[cur][b] = ans;
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	memset(dp, -1, sizeof(dp));

	ll res = t.ways(0, -1, 0) + t.ways(0, -1, 1); res %= mod;
	cout << res << endl;
}