#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; int w; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<int> parent;
	int n;

	graph(int _n) : n(_n) { nodes.resize(n); parent.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
	}

	bool reachable(int u, int v) {
		queue<int> S; vector<bool> vis(n, 0);
		S.push(u); vis[u] = 1;

		while (!S.empty()) {
			int cur = S.front(); S.pop();
			for (auto& e : nodes[cur].edges) {
				if (vis[e.v]) { continue; }
				vis[e.v] = true; S.push(e.v);
				parent[e.v] = e.u;
			}
		}

		return vis[v];
	}

	vector<int> getPath(int u, int v) {
		vector<int> ans;
		while (v != u) {
			ans.push_back(v);
			v = parent[v];
		}
		ans.push_back(u);
		reverse(ans.begin(), ans.end());
		return move(ans);
	}
};

int n, m, d;
vector<edge> edges;
vector<int> checkPath(int maxW) {
	graph g(n);
	for (auto& e : edges) {
		if (e.w > maxW) { continue; }
		g.add_edge(e.u, e.v);
	}
	bool b = g.reachable(0, n - 1);
	vector<int> ans;
	if (b) { ans = g.getPath(0, n - 1); }
	if (ans.size() - 1 > d) { ans = vector<int>(); }
	return move(ans);
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	cin >> n >> m >> d;
	edges.resize(m);
	for (int i = 0; i < m; i++) {
		int u, v, w; cin >> u >> v >> w; u--; v--;
		edges[i] = edge(u, v, w);
	}

	vector<int> ans;
	int l = 0, r = 1e9 + 1;
	while (l < r) {
		int mid = (l + r) / 2;		
		vector<int> cur = checkPath(mid);
		if (!cur.empty()) { ans = cur; r = mid; }
		else { l = mid + 1; }
	}

	if (r == 1e9 + 1) { cout << -1 << '\n'; return 0; }

	cout << ans.size() - 1 << '\n';
	for (auto& x : ans) { cout << x + 1 << ' '; }
}