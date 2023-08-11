#include <bits/stdc++.h>
using namespace std;
vector<int> c, res;

struct Edge {
	int u, v; Edge() {}
	Edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct Node { vector<Edge> edges; };

struct Tree {
	vector<Node> nodes;
	set<int> childS;	//Contains the set of the last Node we called dfs on
	int n;

	Tree(int _n) : n(_n) { nodes.resize(n); }

	void addEdge(int u, int v) {
		Edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		set<int> curS;
		curS.insert(c[u]);
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			if (childS.size() > curS.size()) { swap(childS, curS); }
			for (auto &x : childS) { curS.insert(x); }
		}
		res[u] = curS.size();
		swap(childS, curS);
	}
};

int main() {
	int n; cin >> n;
	c.resize(n); res.resize(n);
	Tree t(n);

	for (int i = 0; i < n; i++) { cin >> c[i]; }
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.addEdge(u, v);
	}

	t.dfs(0, -1);
	for (auto &x : res) { cout << x << " "; }
	cout << '\n';
}