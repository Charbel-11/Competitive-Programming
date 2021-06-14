#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;
typedef long long ll;

struct DSU {
	vector<int> rank, parent;
	DSU(int n) {
		rank.resize(n, 1); parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}
	int find(const int u) { return parent[u] == u ? u : (parent[u] = find(parent[u])); }
	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u;
		return true;
	}
};

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
	bool operator < (const edge& rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1); m++;
	}

	ll KruskalMST(int i) {
		DSU dsu(n); vector<edge> res;
		while (i < m && res.size() != n - 1) {
			edge& e = edges[i];
			if (!dsu.merge(e.u, e.v)) { i++; continue; }
			res.push_back(e);
		}
		if (res.size() != n - 1) { res.clear(); return -1; }
		return res.back().w - res[0].w;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for(int i = 0; i < m; i++){
		int u, v; ll w; cin >> u >> v >> w;
		u--; v--;
		g.add_edge(u, v, w);
	}
	sort(g.edges.begin(), g.edges.end());

	ll ans = -1;
	for (int i = 0; i < m; i++) {
		ll cur = g.KruskalMST(i);
		if (ans == -1) { ans = cur; }
		else if (cur != -1) { ans = min(ans, cur); }
	}
	
	if (ans == -1) { cout << "NO" << '\n'; return 0; }
	cout << "YES" << '\n';
	cout << ans << '\n';
}