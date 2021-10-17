#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <numeric>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

struct DSU {
	vector<int> parent, maxV;
	vector<ll> rank;

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n); maxV.resize(n);
		iota(parent.begin(), parent.end(), 0);
		iota(maxV.begin(), maxV.end(), 0);
	}

	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	ll size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		maxV[u] = max(maxV[u], maxV[v]);
		return true;
	}
};

ll mergeRange(int u, int v, DSU& dsu) {
	ll oldAns = 0, newAns = 0;

	u = dsu.maxV[dsu.find(u)];
	if (u >= v) { return 0; }

	oldAns += (dsu.size(u) * (dsu.size(u) - 1)) / 2; oldAns %= mod;
	while (u < v) {
		oldAns += (dsu.size(u + 1) * (dsu.size(u + 1) - 1)) / 2; oldAns %= mod;
		dsu.merge(u, u + 1);
		u = dsu.maxV[dsu.find(u)];
	}

	newAns = (dsu.size(u) * (dsu.size(u) - 1)) / 2; newAns %= mod;
	newAns -= oldAns; newAns %= mod;
	if (newAns < 0) { newAns += mod; }
	return newAns;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	ifstream ifs("in.txt");
	ofstream ofs("out.txt");

	int t; ifs >> t;
	for (int qq = 1; qq <= t; qq++) {
		ll n, m; ifs >> n >> m;
		DSU dsu(n);

		ll ans = 1, lastAns = n * (n - 1) / 2; lastAns %= mod;
		for (int i = 0; i < m; i++) {
			int a, b; ifs >> a >> b; a--; b--;
			if (a > b) { swap(a, b); }

			ll cur = lastAns;
			cur += mergeRange(a, b, dsu);
			cur %= mod;

			ans *= cur; ans %= mod;
			lastAns = cur;
		}

		ofs << "Case #" << qq << ": " << ans << '\n';
	}
}