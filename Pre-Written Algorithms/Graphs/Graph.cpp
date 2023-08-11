#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int u, v; int w; Edge() {}
	Edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct Node { vector<Edge> edges; };

struct Graph {
	vector<Node> nodes;
	int n;

	Graph(int _n) : n(_n) { nodes.resize(n); }

	void addEdge(int u, int v) {
		Edge e1(u, v); nodes[u].edges.push_back(e1);
		Edge e2(v, u); nodes[v].edges.push_back(e2);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	Graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.addEdge(u, v);
	}
}