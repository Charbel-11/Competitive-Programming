#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { int inDeg = 0, outDeg = 0; vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
		nodes[u].outDeg++; nodes[v].inDeg++;
	}

	bool cycle_dfs(int u, vector<int>& color, vector<int>& parent) {
		color[u] = 1;
		for (auto& e : nodes[u].edges) {
			int v = e.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color, parent)) { return true; }
			}
			else if (color[v] == 1) { parent[v] = u; return true; }	//One node in the cycle would be u or v
		}
		color[u] = 2; return false;
	}
	bool find_cycle() {
		vector<int> color(n, 0), parent(n, -1);
		for (int v = 0; v < n; v++)
			if (cycle_dfs(v, color, parent)) { return true; }
		return false;
	}

	void dfs(int u, vector<int>& visited, vector<int>& ans) {
		visited[u] = true;
		for (auto& e : nodes[u].edges) {
			int v = e.v;
			if (!visited[v]) { dfs(v, visited, ans); }
		}
		ans.push_back(u);
	}
	vector<int> topological_sort() {
		vector<int> visited(n, false), ans;
		for (int i = 0; i < n; ++i)
			if (!visited[i]) { dfs(i, visited, ans); }
		reverse(ans.begin(), ans.end());
		return move(ans);
	}

	void dfsC(int u, int cnt, vector<int>& ans) {
		ans[u] = cnt;
		if (!nodes[u].edges.empty())
			dfsC(nodes[u].edges[0].v, cnt, ans);
	}
	vector<int> findComponents() {
		vector<int> ans(n, -1);
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			if (nodes[i].inDeg) { continue; }
			dfsC(i, cnt++, ans);
		}
		return move(ans);
	}

	void print(int u) {
		cout << u + 1 << ' ';
		if (!nodes[u].edges.empty())
			print(nodes[u].edges[0].v);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, k; cin >> n >> k;
	vector<int> p(n); for (auto& x : p) { cin >> x; x--; }

	graph gK(n), gK2(n); bool OK = true;
	for (int i = 0; i < k; i++) {
		int u, v; cin >> u >> v; u--; v--;
		if (gK.nodes[u].outDeg || gK.nodes[v].inDeg) { OK = false; }
		gK.add_edge(u, v);
		gK2.add_edge(u, v);
	}
	if (gK.find_cycle()) { OK = false; }
	if (!OK) { cout << 0 << '\n'; return 0; }

	vector<int> comp = gK.findComponents();
	int cnt = *max_element(comp.begin(), comp.end()) + 1;

	graph g(cnt);
	for (int i = 0; i < n; i++) {
		if (p[i] == -1) { continue; }
		gK2.add_edge(p[i], i);
		int u = comp[p[i]], v = comp[i];
		if (u == v) { continue; }
		g.add_edge(u, v);
	}
	if (g.find_cycle() || gK2.find_cycle()) { OK = false; }
	if (!OK) { cout << 0 << '\n'; return 0; }

	vector<int> compHead(cnt, -1);
	for (int i = 0; i < n; i++) {
		int cur = comp[i];
		if (compHead[cur] == -1 && !gK.nodes[i].inDeg) { compHead[cur] = i; }
	}

	vector<int> topSort = g.topological_sort();
	for (int& c : topSort) {
		gK.print(compHead[c]);
	}
}