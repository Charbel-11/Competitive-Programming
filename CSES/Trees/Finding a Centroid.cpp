#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

struct edge {
	int u, v; ll w;
	edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct Tree {
	vector<node> nodes;
	vector<int> sz;
	int root, n;
	int subtreeN;

	Tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); sz.resize(n, 1); }

	void add_edge(int u, int v, ll w = 1ll) {
		edge e1(u, v, w); edge e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	int getCentroid(int root) {
		getSize(root, -1);
		subtreeN = sz[root];
		return findCentroid(root, -1);
	}
	void getSize(int u, int p) {
		sz[u] = 1;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			getSize(e.v, u);
			sz[u] += sz[e.v];
		}
	}
	int findCentroid(int u, int p) {
		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }
			if (sz[e.v] > subtreeN / 2) { return findCentroid(e.v, u); }
		}
		return u;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n; cin >> n;
	Tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	cout << t.getCentroid(0) + 1 << '\n';
}