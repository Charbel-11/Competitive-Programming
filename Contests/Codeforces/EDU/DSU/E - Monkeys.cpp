#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

vector<int> ans;

struct DSU {
	vector<int> parent;
	vector<set<int>> children;

	DSU(int n) {
		parent.resize(n); children.resize(n);
		iota(parent.begin(), parent.end(), 0);
		for (int i = 0; i < n; i++) { children[i].insert(i); }
	}

	int find(int u) { return parent[u]; }
	int size(int u) { return children[parent[u]].size(); }

	bool merge(int u, int v, int c) {
		u = parent[u]; v = parent[v]; if (u == v) { return false; }
		if (c != -1) {
			if (u == parent[0]){ 
				for (auto& x : children[v]) ans[x] = c;
			}
			else if (v == parent[0]) {
				for (auto& x : children[u]) ans[x] = c;
			}
		}
		if (size(u) < size(v)) { swap(u, v); }
		set<int>& min = children[v], & max = children[u];

		for (auto& x : min) {
			parent[x] = u; max.insert(x);
		}
		min.clear(); return true;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	vector<pair<int, int>> hands(n), queries(m);
	vector<pair<bool, bool>> releases(n, { 0,0 });
	for (auto& h : hands) { cin >> h.first >> h.second; h.first--; h.second--; }
	for (int i = 0; i < m; i++) {
		int p, h; cin >> p >> h; p--;
		if (h == 1) { releases[p].first = true; }
		else { releases[p].second = true; }
		queries[i] = { p,h };
	}

	DSU dsu(n);
	for (int i = 0; i < n; i++) {
		if (hands[i].first != -2 && !releases[i].first) { dsu.merge(i, hands[i].first, -1); }
		if (hands[i].second != -2 && !releases[i].second) { dsu.merge(i, hands[i].second, -1); }
	}

	ans.resize(n, -1);
	for (int i = m - 1; i >= 0; i--) {
		int cur = queries[i].first, root = dsu.find(0);

		if (queries[i].second == 1) {
			dsu.merge(cur, hands[cur].first, i);
		}
		else {
			dsu.merge(cur, hands[cur].second, i);
		}
	}

	for (auto& x : ans) { cout << x << '\n'; }
}