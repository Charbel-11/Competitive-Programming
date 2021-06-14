#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

struct DSU {
	vector<int> parent, depth;
	vector<set<int>> children;

	DSU(int n) {
		parent.resize(n); children.resize(n);
		depth.resize(n, 0);
		iota(parent.begin(), parent.end(), 0);
		for (int i = 0; i < n; i++) { children[i].insert(i); }
	}

	int find(int u) { return parent[u]; }
	int size(int u) { return children[parent[u]].size(); }

	bool merge(int u, int v) {
		bool flip = depth[u] == depth[v];
		u = parent[u]; v = parent[v];
		if (u == v) { return false; }
		if (size(u) < size(v)) { swap(u, v); }
		set<int>& min = children[v], & max = children[u];

		for (auto& x : min) {
			parent[x] = u; max.insert(x);
			if (flip) { depth[x]++; depth[x] %= 2; }
		}
		min.clear(); return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	bool done = false; int i = 1;
	while (m--) {
		int u, v; cin >> u >> v; u--; v--;
		if (done) { continue; }
		if (dsu.find(u) != dsu.find(v)) { dsu.merge(u, v); }
		else if (dsu.depth[u] == dsu.depth[v]) { cout << i << '\n'; done = true; }
		i++;
	}
	if (!done) { cout << -1 << '\n'; }
}