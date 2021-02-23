#include <iostream>
#include <vector>
#include <set>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;	int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	bool graphColoringUtil(int m, vector<int> &color, int v) {
		if (v == n) { return true; }
		set<int> used;
		for (auto &x : nodes[v].edges) { used.insert(color[x.v]); }
		for (int c = 1; c <= m; c++) {
			if (!used.count(c)) {
				color[v] = c;
				if (graphColoringUtil(m, color, v + 1)) { return true; }
				color[v] = 0;
			}
		}
		return false;
	}
	void graphColoring(int m) {
		vector<int> color(n);
		for (int i = 0; i < n; i++) { color[i] = 0; }
		graphColoringUtil(m, color, 0);
		for (int i = 0; i < n; i++)
			cout << i + 1 << ' ' << color[i] << endl;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	cin.ignore(2); return 0;
}