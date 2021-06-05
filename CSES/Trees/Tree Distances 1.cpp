#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<int> ans;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { multiset<int> childH; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> h;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); h.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs1(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs1(e.v, u);
			nodes[u].childH.insert(h[e.v]);
		}

		if (!nodes[u].childH.empty()) { h[u] = *(nodes[u].childH.rbegin()) + 1; }
	}

	void dfs2(int u, int p) {
		ans[u] = h[u];
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }

			nodes[u].childH.erase(nodes[u].childH.find(h[e.v])); h[u] = 0;
			if (!nodes[u].childH.empty()) { h[u] = *(nodes[u].childH.rbegin()) + 1; }
			nodes[e.v].childH.insert(h[u]);
			h[e.v] = *(nodes[e.v].childH.rbegin()) + 1;

			dfs2(e.v, u);

			nodes[e.v].childH.erase(nodes[e.v].childH.find(h[u])); h[e.v] = 0;
			if (!nodes[e.v].childH.empty()) { h[e.v] = *(nodes[e.v].childH.rbegin()) + 1; }
			nodes[u].childH.insert(h[e.v]);
			h[u] = *(nodes[u].childH.rbegin()) + 1;
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	ans.resize(n);
	t.dfs1(0, -1);
	t.dfs2(0, -1);

	for (auto &x : ans) { cout << x << ' '; }
	cout << '\n';
}