#include <iostream>
#include <vector>
#include <numeric>
#include <bitset>
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

bitset<100001> dp;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		dsu.merge(u, v);
	}
	
	vector<int> nums;
	vector<bool> used(n, 0);
	for (int i = 0; i < n; i++) {
		int curH = dsu.find(i);
		if (used[curH]) { continue; }
		used[curH] = true;
		nums.push_back(dsu.size(curH));
	}

	dp[0] = 1;
	for (int i = 0; i < nums.size(); i++) {
		dp |= (dp << nums[i]);
	}

	string ans(n, '0');
	for (int i = 1; i <= n; i++) {
		if (dp[i]) { ans[i - 1] = '1'; }
	}
	cout << ans << '\n';
}