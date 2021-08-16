#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
using namespace std;
typedef long long ll;

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

	bool sameComp(int u, int v) {
		return find(u) == find(v);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m1, m2; cin >> n >> m1 >> m2;
	DSU g1(n), g2(n);

	for (int i = 0; i < m1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g1.merge(u, v);
	}
	for (int i = 0; i < m2; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g2.merge(u, v);
	}

	int ans = 0;
	vector<pair<int, int>> addedEdges;
	for (int u = 0; u < n; u++) {
		for (int v = u + 1; v < n; v++) {
			if (!g1.sameComp(u, v) && !g2.sameComp(u, v)){
				ans++;
				g1.merge(u, v); g2.merge(u, v);
				addedEdges.push_back({ u + 1,v + 1 });
			}
		}
	}

	cout << ans << '\n';
	for (auto& e : addedEdges) { cout << e.first << " " << e.second << '\n'; }
}