#include <iostream>
#include <string>
#include <map>
#include <set>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;


struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :u(_u), v(_v) {}
};
struct node { vector<edge> edges; };

struct tree {
	int n;
	vector<node> nodes;
	vector<int> sz;
	tree(int _n) :n(_n) { nodes.resize(n); sz.resize(n, 1); }

	void add_edge(int u, int v) {
		nodes[u].edges.push_back(edge(u, v));
		nodes[v].edges.push_back(edge(v, u));
	}

	void dfs(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);
			sz[u] += sz[e.v];
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 1; i < n; i++) {
		int u; cin >> u; u--;
		t.add_edge(i, u);
	}

	t.dfs(0, -1);
	for (int i = 0; i < n; i++) {
		cout << t.sz[i] - 1 << ' ';
	}cout << '\n';
}