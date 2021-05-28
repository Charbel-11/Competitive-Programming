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
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int p, h; vector<edge> edges; };

struct tree {
	vector<node> nodes;
	vector<int> subP;
	int root, n, m;

	tree(int _n, int _m, int _r = 0) : n(_n), m(_m), root(_r) { nodes.resize(n); subP.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	pair<int, int> dfs(int u, int p) {
		int subH = 0, subS = 0;
		subP[u] = nodes[u].p;

		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			auto p = dfs(e.v, u);
			subP[u] += subP[e.v];
			if (p.first == -1 && p.second == -1) { return { -1,-1 }; }
			subH += p.first; subS += p.second;
		}

		if ((nodes[u].h + subP[u]) % 2) { return { -1,-1 }; }
		int tH = (nodes[u].h + subP[u]) / 2;
		int tS = subP[u] - tH;
		if (tH - tS != nodes[u].h || tS < 0) { return { -1,-1 }; }

		if (subH > tH){ return { -1,-1 }; }
		return { tH, tS };
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		tree t(n, m);
		for (int i = 0; i < n; i++) { cin >> t.nodes[i].p; }
		for (int i = 0; i < n; i++) { cin >> t.nodes[i].h; }

		for (int i = 0; i < n - 1; i++) {
			int u, v; cin >> u >> v; u--; v--;
			t.add_edge(u, v);
		}

		pair<int, int> ans = t.dfs(0, -1);
		if (ans.first == -1 || ans.second == -1) { cout << "NO\n"; }
		else { cout << "YES\n"; }
	}
}