#include <iostream>
#include <vector>
#include <numeric>
#include <set>
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

	int n, m, k; cin >> n >> m >> k;
	set<pair<int, int>> edges;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		if (u > v) { swap(u, v); }
		edges.insert({ u,v });
	}

	vector<pair<int, int>> breakdowns;
	for (int i = 0; i < k; i++) {
		int u, v; cin >> u >> v; u--; v--;
		if (u > v) { swap(u, v); }
		edges.erase({ u,v });
		breakdowns.push_back({ u,v });
	}

	int comp = n; DSU dsu(n);
	for (auto& e : edges) {
		comp -= dsu.merge(e.first, e.second);
	}

	vector<int> ans(k);
	for (int i = k - 1; i >= 0; i--) {
		ans[i] = comp;
		comp -= dsu.merge(breakdowns[i].first, breakdowns[i].second);
	}

	for (auto& x : ans) { cout << x << ' '; }
	cout << '\n';
}