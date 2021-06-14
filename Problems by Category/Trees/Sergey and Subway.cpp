#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = 1e17;
ll odd, answ;

struct edge {
	int u, v;
	edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct tree {
	vector<node> nodes; vector<ll> sz;
	int root; ll n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); sz.resize(n, 1ll); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}
	
	void dfs(int u, int p, bool o) {
		if (o) { odd++; }
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, !o);
			sz[u] += sz[e.v];
			answ += (sz[e.v] * (n - sz[e.v]));
		}
	}
};

int main() {
	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	odd = answ = 0;
	t.dfs(0, -1, 0);
	answ = (answ - (odd*(n - odd))) / 2 + odd*(n - odd);
	cout << answ << endl;
}