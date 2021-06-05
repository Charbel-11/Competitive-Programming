#include <iostream>
#include <vector>
#include <stack>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes[2]; int n;
	graph(int _n) : n(_n) { nodes[0].resize(n); nodes[1].resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[0][u].edges.push_back(e1);
		nodes[1][v].edges.push_back(e2);
	}

	void scc_dfs1(int v, vector<bool> &used, vector<int> &order) {
		used[v] = true;
		for (auto &x : nodes[0][v].edges)
			if (!used[x.v]) { scc_dfs1(x.v, used, order); }
		order.push_back(v);
	}

	void scc_dfs2(int v, vector<bool> &used, vector<int> &component) {
		used[v] = true;
		component.push_back(v);
		for (auto &x : nodes[1][v].edges)
			if (!used[x.v]) { scc_dfs2(x.v, used, component); }
	}

	vector<vector<int>> SCC() {
		vector<bool> used(n, false);
		vector<int> order, component;
		vector<vector<int>> scc;
		for (int i = 0; i < n; i++)
			if (!used[i]) { scc_dfs1(i, used, order); }
		used.assign(n, false);
		for (int i = 0; i < n; i++) {
			int v = order[n - 1 - i];
			if (!used[v]) {
				scc_dfs2(v, used, component);
				scc.push_back(component);
				component.clear();
			}
		}
		return move(scc);
	}

	void dfs(int u, vector<bool> &visited) {
		visited[u] = 1;  
		stack<int> S; S.push(u);

		while (!S.empty()) {
			int cur = S.top(); S.pop();
			for (auto &e : nodes[0][cur].edges) {
				if (visited[e.v]) { continue; }
				visited[e.v] = 1; S.push(e.v);
			}
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<vector<int>> scc = g.SCC();
	if (scc.size() == 1) { cout << "YES\n"; return 0; }
	cout << "NO\n";

	vector<bool> visited(n, 0);
	g.dfs(scc[0][0], visited);
	int u = scc[0][0], v = -1;
	for (int i = 0; i < n; i++) {
		if (!visited[i]) { v = i; break; }
	}
	if (v == -1) { u = scc[1][0]; v = scc[0][0]; }
	cout << u + 1 << ' ' << v + 1 << '\n';
}