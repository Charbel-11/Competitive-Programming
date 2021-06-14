#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
	vector<int> rank, parent;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct op {
	bool ask;
	int u, v;

	op(bool a, int _u, int _v) :ask(a), u(_u), v(_v) {}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	
	int n, m, k; cin >> n >> m >> k;
	DSU dsu(n);
	while (m--) {
		int u, v; cin >> u >> v;
	}
	vector<op> ops;
	while (k--) {
		string t; cin >> t;
		int u, v; cin >> u >> v; u--; v--;
		ops.push_back(op(t[0] == 'a', u, v));
	}

	vector<string> ans;
	reverse(ops.begin(), ops.end());
	for (auto& o : ops) {
		if (o.ask) { ans.push_back(dsu.find(o.u) == dsu.find(o.v) ? "YES" : "NO"); }
		else {
			dsu.merge(o.u, o.v);
		}
	}

	reverse(ans.begin(), ans.end());
	for (auto& x : ans) { cout << x << '\n'; }
}