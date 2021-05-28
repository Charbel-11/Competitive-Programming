#include <iostream>
#include <vector>
#include <numeric>
#include <map>
using namespace std;
typedef long long ll;

struct DSU {
	vector<ll> rank; 
	vector<int> parent;

	DSU(int n) {
		rank.resize(n, 1ll); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	ll size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

int main() {
	int n, m; cin >> n >> m;
	DSU dsu(n);

	map<ll, vector<pair<int, int>>> weights;
	for (int i = 0; i < n - 1; i++) {
		int u, v; ll w; cin >> u >> v >> w;
		u--; v--;

		weights[w].push_back({ u,v });
	}

	map<ll, ll> answ;
	ll prev = 0;
	for (auto &it : weights) {
		for (auto &p : it.second) {
			int u = p.first, v = p.second;
			answ[it.first] += dsu.size(u)*dsu.size(v);
			dsu.merge(u, v);
		}
		answ[it.first] += prev;
		prev = answ[it.first];
	}

	for (int i = 0; i < m; i++) {
		int q; cin >> q;
		auto it = answ.upper_bound(q);
		if (it == answ.begin()) { cout << 0 << " "; continue; }
		it--;
		cout << it->second << " ";
	}cout << endl;
}