#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

struct DSU {
	vector<int> rank, parent, minV, maxV;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		minV.resize(n); maxV.resize(n);
		iota(parent.begin(), parent.end(), 0);
		iota(maxV.begin(), maxV.end(), 0);
		iota(minV.begin(), minV.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		minV[u] = min(minV[u], minV[v]);
		maxV[u] = max(maxV[u], maxV[v]);
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
		if (t[0] == 'u') {
			int u, v; cin >> u >> v; u--; v--;
			dsu.merge(u, v);
		}
		else {
			int u; cin >> u; u--;
			u = dsu.find(u);
			cout << dsu.minV[u] + 1 << " " << dsu.maxV[u] + 1 << " " << dsu.rank[u] << '\n';
		}
	}
}