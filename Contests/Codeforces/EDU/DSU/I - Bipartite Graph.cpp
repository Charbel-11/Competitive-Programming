#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Maintains the parity of the distance of each node to its root
//Even though the parent edges aren't represented as is (so this works for parity only; not for actual distance)
struct DSU {
	vector<int> rank, parent, dist;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		dist.resize(n, 0);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { 
		if (parent[u] == u) { return u; }
		find(parent[u]);
		dist[u] += dist[parent[u]]; dist[u] %= 2;
		return parent[u] = parent[parent[u]]; 
	}
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		int ru = find(u), rv = find(v);
		if (ru == rv) { return false; }
		if (rank[ru] < rank[rv]) { swap(ru, rv); swap(u, v); }
		rank[ru] += rank[rv]; parent[rv] = ru;
		dist[rv] = 1 + dist[u] + dist[v]; dist[rv] %= 2;
		return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n); int shift = 0;
	while (m--) {
		int t, u, v; cin >> t >> u >> v; u--; v--;
		u += shift; u %= n;
		v += shift; v %= n;
		if (t == 0) {
			dsu.merge(u, v);
		}
		else {
			dsu.find(u); dsu.find(v);
			bool ans = dsu.dist[u] == dsu.dist[v];
			shift += ans; shift %= n;
			cout << (ans ? "YES" : "NO") << '\n';
		}
	}
}