#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

vector<bool> neededParity, curParity;
vector<int> ans;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void dfs(int u, vector<bool>& vis) {
		vis[u] = true;
		ans.push_back(u);
		curParity[u] = !curParity[u];

		for (auto& e : nodes[u].edges) {
			if (vis[e.v]) { continue; }
			dfs(e.v, vis);
			if (neededParity[e.v] != curParity[e.v]) {
				ans.push_back(u); ans.push_back(e.v);
				curParity[e.v] = !curParity[e.v];
				curParity[u] = !curParity[u];
			}
			ans.push_back(u);
			curParity[u] = !curParity[u];
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n); neededParity.resize(n); curParity.resize(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	string s; cin >> s;
	for (int i = 0; i < n; i++) { neededParity[i] = s[i] == '1'; curParity[i] = 0; }

	vector<bool> vis(n, 0);
	g.dfs(0, vis);

	if (neededParity[0] != curParity[0]) {
		int v = g.nodes[0].edges[0].v;
		ans.push_back(v); ans.push_back(0); ans.push_back(v);
	}

	cout << ans.size() << '\n';
	for (auto& x : ans) { cout << x + 1 << " "; }
	cout << '\n';
}