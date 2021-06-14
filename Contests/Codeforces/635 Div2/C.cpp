#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;

struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> depth, subtreeSize;
	int root, n;

	tree() {}
	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); depth.resize(n, 0); subtreeSize.resize(n, 0); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p) {
		subtreeSize[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			depth[e.v] = depth[u] + 1;
			dfs(e.v, u);
			subtreeSize[u] += subtreeSize[e.v];
		}
	}
};

int main() {
	int n, k; cin >> n >> k;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.dfs(0, -1);
	vector<int> gains;
	for (int i = 0; i < n; i++) {
		gains.push_back(t.depth[i] - (t.subtreeSize[i] - 1));
	}
	sort(gains.rbegin(), gains.rend());
	ll ans = 0;
	for (int i = 0; i < k; i++) { ans += gains[i]; }
	cout << ans << endl;
}