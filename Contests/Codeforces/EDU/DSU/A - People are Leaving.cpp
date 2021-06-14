#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct DSU {
	vector<int> rank, parent, maxV;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n); maxV.resize(n);
		iota(parent.begin(), parent.end(), 0);
		iota(maxV.begin(), maxV.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		maxV[u] = max(maxV[u], maxV[v]);
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n + 1);
	while (m--) {
		char c; cin >> c;
		int x; cin >> x; x--;
		if (c == '?') {
			int ans = dsu.maxV[dsu.find(x)] + 1;
			if (ans == n + 1) { cout << -1 << '\n'; }
			else { cout << ans << '\n'; }
		}
		else {
			dsu.merge(x, x + 1);
		}
	}
}