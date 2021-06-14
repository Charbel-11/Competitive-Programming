#include <iostream>
#include <vector>
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

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	while (m--) {
		string t; cin >> t;
		int u, v; cin >> u >> v; u--; v--;
		if (t[0] == 'u') {
			dsu.merge(u, v);
		}
		else {
			cout << (dsu.find(u) == dsu.find(v) ? "YES" : "NO") << '\n';
		}
	}
}