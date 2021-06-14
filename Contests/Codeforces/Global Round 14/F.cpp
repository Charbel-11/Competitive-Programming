#include <iostream>
#include <vector>
#include <unordered_map>
#include <numeric>
#include <map>
using namespace std;
typedef long long ll;
ll x;

struct DSU {
	vector<int> rank, parent;
	vector<ll> asph;
	vector<unordered_map<int, int>> edges;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n); 
		asph.resize(n, 0); edges.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }

	void merge(int &u, int &v) {
		u = find(u); v = find(v);
		if (rank[u] < rank[v]) { swap(u, v); }

		rank[u] += rank[v];	parent[v] = u;
		asph[u] += asph[v] - x;

		if (edges[u].size() < edges[v].size()) { swap(edges[u], edges[v]); }
		for (auto& x : edges[v]) {
			if (find(x.first) == u) { continue; }
			edges[u][x.first] = x.second;
		}
		edges[v].clear();
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m >> x;
	DSU dsu(n); multimap<ll, int> asphToComp; 
	ll S = 0;
	for (int i = 0; i < n; i++) { cin >> dsu.asph[i]; asphToComp.insert({ dsu.asph[i], i }); S += dsu.asph[i]; }
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		dsu.edges[u].insert({ v, i });
		dsu.edges[v].insert({ u, i });
	}

	if (S < x * (n - 1)) { cout << "NO" << '\n'; return 0; }

	vector<int> ans;
	for (int i = 0; i < n - 1; i++) {
		auto maxIt = prev(asphToComp.end());
		int u = maxIt->second;
		while (dsu.find(u) != u ||  dsu.asph[u] != maxIt->first) {
			asphToComp.erase(maxIt);
			maxIt = prev(asphToComp.end());
			u = maxIt->second;
		}
		asphToComp.erase(maxIt);

		auto adjIt = dsu.edges[u].begin();
		int v = adjIt->first;
		while (dsu.find(v) == u) {
			dsu.edges[u].erase(adjIt);
			adjIt = dsu.edges[u].begin();
			v = adjIt->first;
		}
		ans.push_back(adjIt->second);

		dsu.merge(u, v); 
		asphToComp.insert({ dsu.asph[u], u });
	}

	cout << "YES" << '\n'; 
	for (auto& xx : ans) { cout << xx + 1 << '\n'; }
}