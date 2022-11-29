#include <bits/stdc++.h>
using namespace std;

struct DSU {
	int time = 0;
	vector<int> parent;
	vector<vector<int>> children;
	vector<vector<pair<int, int>>> history;

	DSU(int n) : parent(n), children(n), history(n) {
		iota(parent.begin(), parent.end(), 0);
		for (int i = 0; i < n; i++) { children[i].push_back(i); }
	}

	int size(const int u) const { return (int)children[parent[u]].size(); }

	bool merge(int u, int v, const int w) {
		u = parent[u]; v = parent[v];
		if (u == v) { return false; }

		if (size(u) > size(v)) { swap(u, v); }
		for (auto& x : children[u]) {
			history[x].push_back({ time, w });
			parent[x] = v; children[v].push_back(x);
		}
		time++; children[u].clear();
		return true;
	}

	// Finds the (time, value) pair of the first edge that connected u and v in O(loglogn)
	// Assumes u != v
	pair<int, int> query(int u, int v) const {
		if (parent[u] != parent[v]) { return { -1,-1 }; }
		if (history[u].size() > history[v].size()) { swap(u, v); }

		int l = 0, r = history[u].size();
		while (l != r) {
			int mid = (l + r) >> 1;
			if ((history[u].rbegin() + mid)->first == (history[v].rbegin() + mid)->first) { l = mid + 1; }
			else { r = mid; }
		}
		if (l == (int)history[u].size()) { return *(history[v].rbegin() + l); }
		return max(*(history[v].rbegin() + l), *(history[u].rbegin() + l));
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);


}