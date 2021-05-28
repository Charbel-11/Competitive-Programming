#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<int> c;
vector<vector<int>> order;

void add(vector<int>& v1, vector<int>& v2) {
	for (auto &x : v2)
		v1.push_back(x);
}

struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> size;
	int n, root;

	tree(int _n) : n(_n) { nodes.resize(n); size.resize(n, 1); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {

		for (auto e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u);

			add(order[u], order[e.v]);
			size[u] += size[e.v];
		}

		if (size[u] <= c[u]) { cout << "NO" << endl; exit(0); }

		order[u].insert(order[u].begin() + c[u], u);
	}
};

int main() {
	int n; cin >> n;
	c.resize(n); order.resize(n);
	tree t(n);

	for (int i = 0; i < n; i++) {
		int pi, ci; cin >> pi >> ci;
		if (pi == 0) { t.root = i; }
		else { pi--; t.add_edge(pi, i); }
		c[i] = ci;
	}

	t.dfs(t.root, -1);

	vector<int> res(n);
	for (int i = 0; i < n; i++) {
		res[order[t.root][i]] = i+1;
	}

	cout << "YES" << endl;
	for (auto &x : res) { cout << x << " "; } cout << endl;
}