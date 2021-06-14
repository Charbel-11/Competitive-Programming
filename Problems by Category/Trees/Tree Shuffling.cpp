//https://codeforces.com/contest/1363/problem/E

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

const ll INF = (ll)1e17;
struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node {
	ll c; bool have, want; 
	vector<edge> edges; 
	node() {}
	node(ll _c, int h, int w) :c(_c), have(h), want(w) {}
};

struct tree {
	vector<node> nodes;
	int root, n;
	int ones, zeros;
	int nOnes, nZeros;
	ll res = 0;

	tree(int _n, int _r = 0) : n(_n), root(_r) { ones = zeros = nOnes = nZeros = 0; res = 0; nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int p, ll curC) {
		nOnes += nodes[u].want == 1;
		nZeros += nodes[u].want == 0;
		ones += nodes[u].have == 1;
		zeros += nodes[u].have == 0;

		curC = min(curC, nodes[u].c);
		nodes[u].c = curC;

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs(e.v, u, curC);
		}
	}

	pair<int, int> dfs2(int u, int p) {
		pair<int, int> cur = { 0,0 };
		if (nodes[u].want != nodes[u].have) {
			cur.first += nodes[u].want == 0;
			cur.second += nodes[u].want == 1;
		}
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			auto p = dfs2(e.v, u);
			cur.first += p.first;
			cur.second += p.second;
		}
		int contribution = min(cur.first, cur.second);
		res += 2ll * contribution*nodes[u].c;
		cur.first -= contribution; cur.second -= contribution;
		return cur;
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n;
	tree t(n);
	for (int i = 0; i < n; i++) {
		ll a; int b, c; cin >> a >> b >> c;
		t.nodes[i] = node(a, b, c);
	}

	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}

	t.dfs(0, -1, INT_MAX);
	if (t.nOnes != t.ones || t.nZeros != t.zeros) {
		cout << -1 << '\n'; return 0;
	}
	t.dfs2(0, -1);
	cout << t.res << '\n';
}