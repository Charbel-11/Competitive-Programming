#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}
}