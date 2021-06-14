#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
	}

	bool cycle_dfs(int u, vector<int> &color, vector<int> &parent) {
		color[u] = 1;
		for (auto &e : nodes[u].edges) {
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

	void dfs(int u, vector<int> &visited, vector<int> &ans) {
		visited[u] = true;
		for (auto &e : nodes[u].edges) {
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
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int t; cin >> t;
	while (t--) {
		int n, m; cin >> n >> m;
		vector<pair<int, int>> undEdges, ans;
		graph g(n);

		for (int i = 0; i < m; i++) {
			int type; cin >> type;
			int u, v; cin >> u >> v; u--; v--;
			if (type == 0) { undEdges.push_back({ u,v }); }
			else { g.add_edge(u, v); ans.push_back({ u,v }); }
		}

		if (g.find_cycle()) { cout << "NO\n"; continue; }

		cout << "YES\n";
		vector<int> topSort = g.topological_sort();
		vector<int> idx(n);
		for (int i = 0; i < n; i++) { idx[topSort[i]] = i; }
		
		for (auto e : undEdges) {
			if (idx[e.first] > idx[e.second]) { swap(e.first, e.second); }
			ans.push_back(e);
		}

		for (auto &e : ans) { cout << e.first + 1 << ' ' << e.second + 1 << '\n'; }
	}
}