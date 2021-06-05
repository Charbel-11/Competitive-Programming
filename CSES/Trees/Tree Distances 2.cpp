#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<ll> ans;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> subSize;
	vector<ll> subAns;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); subSize.resize(n, 1); subAns.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs1(int u, int p) {
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs1(e.v, u);
			subAns[u] += (subAns[e.v] + subSize[e.v]);
			subSize[u] += subSize[e.v];
		}
	}

	void dfs2(int u, int p) {
		ans[u] = subAns[u];
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			
			subAns[u] -= (subAns[e.v] + subSize[e.v]);
			subSize[u] -= subSize[e.v];
			subSize[e.v] += subSize[u];
			subAns[e.v] += (subAns[u] + subSize[u]);

			dfs2(e.v, u);

			subAns[e.v] -= (subAns[u] + subSize[u]);
			subSize[e.v] -= subSize[u];
			subSize[u] += subSize[e.v];
			subAns[u] += (subAns[e.v] + subSize[e.v]);
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

	t.dfs1(0, -1); t.dfs2(0, -1);

	for (auto &x : ans) { cout << x << ' '; } cout << '\n';
}