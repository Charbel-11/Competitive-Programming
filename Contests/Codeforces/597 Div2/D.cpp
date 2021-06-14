#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

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
	int u, v; long long w; edge() {}
	edge(int _u, int _v, long long _w) :
		u(_u), v(_v), w(_w) {}
	bool operator < (const edge &rhs) const { return w < rhs.w; }
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n = 0;
	vector<edge> edges; int m = 0;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, long long w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1); m++;
	}

	long long KruskalMST(vector<edge> &res) {
		sort(edges.begin(), edges.end());
		DSU dsu(n); res.clear(); int i = 0; long long ans = 0;
		while (i < m && res.size() != n - 1) {
			edge &e = edges[i];
			if (!dsu.merge(e.u, e.v)) { i++; continue; }
			res.push_back(e); ans += e.w;
			i++;
		}
		if (res.size() != n - 1) { res.clear(); return -1; }
		return ans;
	}
};

vector<pair<long long, long long>> coord;

long long dist(int i, int j) {
	return abs(coord[i].first - coord[j].first) + abs(coord[i].second - coord[j].second);
}

int main() {
	int n; cin >> n;
	graph g(n + 1); coord.resize(n);
	for (int i = 0; i < n; i++) {
		long long x, y; cin >> x >> y;
		coord[i] = { x,y };
	}

	vector<long long> c(n);
	for (auto &x : c) { cin >> x; }
	vector<long long> k(n);
	for (auto &x : k) { cin >> x; }

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) { continue; }
			long long weight = (k[i] + k[j])*dist(i, j);
			g.add_edge(i, j, weight);
		}
	}
	for (int i = 0; i < n; i++) {
		g.add_edge(i, n, c[i]);
	}

	vector<edge> res;
	long long finalC = g.KruskalMST(res);
	vector<int> bought; vector<pair<int, int>> connections;
	for (auto &x : res) {
		if (x.u == n) { bought.push_back(x.v+1); }
		else if (x.v == n) { bought.push_back(x.u+1); }
		else { connections.push_back({ x.u+1, x.v+1 }); }
	}

	cout << finalC << endl;
	cout << bought.size() << endl;
	for (auto &x : bought) { cout << x << " "; } cout << endl;
	cout << connections.size() << endl;
	for (auto &p : connections) {
		cout << p.first << " " << p.second << endl;
	}
}