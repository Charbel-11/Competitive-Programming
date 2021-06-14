#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <climits>
using namespace std;
typedef long long ll;

vector<int> fib;

struct edge {
	int u, v; bool dead = false; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int par = -1; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> subS;
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); subS.resize(n, 1); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs0(int u, int p) {
		nodes[u].par = p;
		for (auto& e : nodes[u].edges) {
			if (e.v == p) { continue; }
			dfs0(e.v, u);
			subS[u] += subS[e.v];
		}
	}

	bool dfs(int u, int i, int r) {
		if (i <= 1) { return true; }

		for (auto& e : nodes[u].edges) {
			if (e.v == nodes[u].par || e.dead) { continue; }
			if (subS[e.v] == fib[i - 1] || subS[e.v] == fib[i - 2]) {
				e.dead = true;

				int cur = u;
				while(true){
					subS[cur] -= subS[e.v];
					if (cur == r) { break; }
					cur = nodes[cur].par;
				}

				if (subS[e.v] == fib[i - 1]) {
					return dfs(e.v, i - 1, e.v) && dfs(r, i - 2, r);
				}
				else if (subS[e.v] == fib[i - 2]) {
					return dfs(e.v, i - 2, e.v) && dfs(r, i - 1, r);
				}
			}
			else { if (dfs(e.v, i, r)) { return true; } }
		}
		return false;
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

	if (n <= 2) { cout << "YES" << '\n'; return 0; }

	fib.push_back(1); fib.push_back(1);
	while (fib.back() < 1e6) { fib.push_back(fib.back() + fib[fib.size() - 2]); }

	t.dfs0(0, -1);
	int idx = -1;
	for (int i = 0; i < fib.size(); i++) {
		if (fib[i] == t.subS[0]) { idx = i; break; }
	}

	if (idx == -1) { cout << "No" << '\n'; return 0; }
	cout << (t.dfs(0, idx, 0) ? "Yes" : "No") << '\n';
}