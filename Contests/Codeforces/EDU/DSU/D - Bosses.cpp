#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

//Works because the merging is always done between roots
struct DSU {
	vector<int> parent, dist;

	DSU(int n) {
		parent.resize(n); dist.resize(n, 0);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { 
		if (parent[u] == u) { return u; }
		find(parent[u]);
		dist[u] += dist[parent[u]];
		return parent[u] = parent[parent[u]];
	}

	void merge(int u, int v) {
		parent[v] = u;
		dist[v] = 1;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	while (m--) {
		int t; cin >> t;
		if (t == 1) {
			int a, b; cin >> a >> b; a--; b--;
			dsu.merge(b, a);
		}
		else {
			int c; cin >> c; c--;
			dsu.find(c);
			cout << dsu.dist[c] << '\n';
		}
	}
}