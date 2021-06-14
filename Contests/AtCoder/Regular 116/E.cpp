#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>
#include <set>
#include <climits>
using namespace std;
typedef long long ll;
const ll INF = 1e17;
int k;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int p; bool done; int maxEval; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<vector<int>> m; 
	int root, n;

	tree(int _n, int _r = 0) : n(_n), root(_r) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs(int u, int d) {
		m[d].push_back(u);
		for (auto& e : nodes[u].edges) {
			if (e.v == nodes[e.u].p) { continue; }
			nodes[e.v].p = e.u;
			dfs(e.v, d + 1);
		}
	}

	void removeAround(int curK, int u, int &doneCnt) {
		if (nodes[u].maxEval == -1) { doneCnt++; nodes[u].done = true; }
		if (nodes[u].maxEval >= curK) { return; }
		nodes[u].maxEval = curK;
		if (curK == 0) { return; }

		for (auto& e : nodes[u].edges)
			removeAround(curK - 1, e.v, doneCnt);
	}

	bool feasible(int t) {
		int curI = n - 1, curJ = 0, curK = k, doneCnt = 0;
		for (int i = 0; i < n; i++) { nodes[i].done = false; nodes[i].maxEval = -1; }

		while (curK > 0 && doneCnt < n) {
			while (curI >= 0 && curJ >= m[curI].size()) { curJ = 0; curI--; }
			if (curI < 0) { break; }
			if (nodes[m[curI][curJ]].done) { curJ++; continue; }

			int tN = m[curI][curJ];
			for (int kk = 0; kk < t; kk++) {
				if (nodes[tN].p == -1) { break; }
				tN = nodes[tN].p;
			}
			removeAround(t, tN, doneCnt);
			curJ++; curK--;
		}
		return (doneCnt == n);
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n; cin >> n >> k;
	tree t(n);
	for (int i = 0; i < n - 1; i++) {
		int u, v; cin >> u >> v; u--; v--;
		t.add_edge(u, v);
	}
	t.nodes[0].p = -1;
	t.m.resize(n); t.dfs(0, 0);

	int l = 0, r = n;
	while (l < r) {
		int mid = (l + r) >> 1;
		if (t.feasible(mid)) { r = mid; }
		else { l = mid + 1; }
	}

	cout << l << '\n';
}