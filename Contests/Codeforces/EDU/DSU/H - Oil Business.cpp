#include <iostream>
#include <vector>
#include <numeric>
#include <set>
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
	int u, v, id; ll w; edge() {}
	edge(int _id, int _u, int _v, ll _w) :
		id(_id), u(_u), v(_v), w(_w) {}
	bool operator < (const edge& rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w) {
		edge e1(m+1, u, v, w), e2(m+1, v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1); m++;
	}

	set<int> KruskalMST() {
		sort(edges.rbegin(), edges.rend());
		DSU dsu(n); set<int> res;
		int i = 0;
		while (i < m && res.size() != n - 1) {
			edge& e = edges[i];
			if (!dsu.merge(e.u, e.v)) { i++; continue; }
			res.insert(e.id);
		}
		return move(res);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	ll s; cin >> s;
	graph g(n);
	for(int i = 0; i < m; i++) {
		int u, v; ll w; cin >> u >> v >> w;
		u--; v--;
		g.add_edge(u, v, w);
	}
	set<int> used = g.KruskalMST();

	vector<int> res;
	for (int i = m - 1; i >= 0; i--) {
		if (s < g.edges[i].w) { break; }
		if (used.count(g.edges[i].id)) { continue; }
		res.push_back(g.edges[i].id);
		s -= g.edges[i].w;
	}

	cout << res.size() << '\n';
	for (auto& x : res) { cout << x << ' '; }
}