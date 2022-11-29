#include <bits/stdc++.h>
using namespace std;

struct DSU {
	vector<int> rank, parent; 

	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}

	int find(const int u) {	return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}	
};