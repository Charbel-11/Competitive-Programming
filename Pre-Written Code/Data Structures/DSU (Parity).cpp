#include <iostream>
#include <set>
#include <vector>
#include <numeric>
using namespace std;

//Maintains the parity of the distance of each node to its root (useful if the graph is assumed to be bipartite)
//Need to call find before using dist
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