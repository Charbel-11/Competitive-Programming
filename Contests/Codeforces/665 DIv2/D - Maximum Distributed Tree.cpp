#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

vector<ll> used;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<ll> subtreeS;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); subtreeS.resize(n, 1); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			subtreeS[u] += subtreeS[e.v];
			used.push_back(subtreeS[e.v] * (n - subtreeS[e.v]));
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int tt; cin >> tt;
	while (tt--) {
		used.clear();
		int n; cin >> n;
		tree t(n);
		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t.add_edge(u, v);
		}

		t.dfs(0, -1); sort(used.begin(), used.end());
		int m; cin >> m;
		vector<ll> pf(m); for (auto &x : pf) { cin >> x; }
		while (pf.size() < n - 1) { pf.push_back(1); }
		sort(pf.begin(), pf.end());
		while (pf.size() > n - 1) {
			ll prod = pf.back() * pf[pf.size() - 2]; prod %= mod;
			pf.pop_back(); pf.pop_back();
			pf.push_back(prod);
		}

		ll ans = 0;
		for (int i = n - 2; i >= 0; i--) {
			ans += pf[i] * used[i];
			ans %= mod;
		}

		cout << ans << '\n';
	}
}