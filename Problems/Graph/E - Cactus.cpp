//https://codeforces.com/contest/231/problem/E
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>
#include <math.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

vector<int> cycleNode;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool topOfCycle = false, special = false; vector<edge> edges; };

//Everything is 0-indexed
struct tree {
	vector<vector<int>> anc;
	vector<node> nodes;
	vector<int> depth, dist;

	int root, n, lg2;

	tree(int _n, int _r = 0) : n(_n), root(_r) {
		lg2 = (int)(ceil(log2(n + 0.0)));
		nodes.resize(n);
		anc.resize(n + 1); for (auto &x : anc) { x.resize(lg2 + 1, -1); }
		depth.resize(n, 0); dist.resize(n, 0);
	}

	void add_edge(int u, int v, bool dir) {
		edge e1(u, v); edge e2(v, u);
		nodes[u].edges.push_back(e1);
		if (!dir) nodes[v].edges.push_back(e2);
	}

	//Copy the constructor
	//Need to call this first
	//Preprocessing takes O(nlogn) time; finds the depth at the same time
	void preprocess() {
		queue<int> q; q.push(root);
		vector<bool> visited(n, false);
		visited[root] = true;
		anc[root][0] = root;
		dist[root] = nodes[root].special;

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (auto &e : nodes[cur].edges) {
				if (visited[e.v]) { continue; }
				anc[e.v][0] = cur;
				depth[e.v] = depth[cur] + 1;
				dist[e.v] = dist[cur] + nodes[e.v].special;
				q.push(e.v); visited[e.v] = true;
			}
		}
		for (int i = 1; i <= lg2; i++)
			for (int u = 0; u < n; u++)
				anc[u][i] = anc[anc[u][i - 1]][i - 1];
	}

	//Need to preprocess before using!
	//Returns the LCA of nodes u and v in O(logn)		
	int LCA(int u, int v) {
		if (depth[u] < depth[v]) { swap(u, v); }

		for (int i = lg2; i >= 0; i--) {
			if (depth[u] - (1 << i) >= depth[v])
				u = anc[u][i];	//furthest parent found is 2^i
		}

		if (u == v) { return v; }

		for (int i = lg2; i >= 0; i--) {
			if (anc[u][i] != anc[v][i]) {
				u = anc[u][i];
				v = anc[v][i];
			}
		}

		return anc[u][0];
	}

	int distance(int u, int v) {
		int lca = LCA(u, v);
		return dist[u] + dist[v] - 2 * dist[lca] + nodes[lca].special;
	}

	void dfs(int u, int p, int &cnt, vector<bool> &vis) {
		vis[u] = 1;
		for (auto &e : nodes[u].edges) {
			if (e.v == p) { continue; }
			if (vis[e.v] && cycleNode[e.v] == e.v) {
				nodes[e.v].topOfCycle = true;
				cycleNode[e.v] = cycleNode[u] = cnt++;
			}
			if (vis[e.v]) { continue; }
			dfs(e.v, u, cnt, vis);
			if (cycleNode[e.v] != e.v && !nodes[e.v].topOfCycle) { cycleNode[u] = cycleNode[e.v]; }
		}
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	tree g(n); cycleNode.resize(n);
	iota(cycleNode.begin(), cycleNode.end(), 0);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v, 0);
	}
	vector<bool> vis(n, 0);
	int cnt = n;
	g.dfs(0, -1, cnt, vis);

	int special = cnt - n;
	for (int i = 0; i < n; i++) {
		if (cycleNode[i] == i) { cycleNode[i] = cnt++; }
	}
	int newN = cnt - n;

	tree t(newN);
	for (int i = 0; i < n; i++) {
		int u = cycleNode[i] - n;
		if (u < special) { t.nodes[u].special = 1; }
		for (auto &e : g.nodes[i].edges) {
			int v = cycleNode[e.v] - n;
			if (u != v) { t.add_edge(u, v, 1); }
		}
	}
	
	vector<ll> ans(n + 2, 0);
	ans[0] = 1;
	for (int i = 1; i < n + 2; i++) {
		ans[i] = ans[i - 1] * 2; ans[i] %= mod;
	}

	t.preprocess();
	int k; cin >> k;
	while (k--) {
		int x, y; cin >> x >> y; x--; y--;
		int dd = t.distance(cycleNode[x] - n, cycleNode[y] - n);
		cout << ans[dd] << '\n';
	}
}