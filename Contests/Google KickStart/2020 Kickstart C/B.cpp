#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
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

	void add_edge(int u, int v, int w = 0) {
		edge e1(u, v);
		nodes[u].edges.push_back(e1);
	}

	bool cycle_dfs(int u, vector<int> &color, vector<int> &parent) {
		color[u] = 1;
		for (auto x : nodes[u].edges) {
			int v = x.v;
			if (color[v] == 0) {
				parent[v] = u;
				if (cycle_dfs(v, color, parent)) { return true; }
			}
			else if (color[v] == 1) { return true; }
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
		for (auto x : nodes[u].edges) {
			int v = x.v;
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
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int t; cin >> t;

	for (int qq = 1; qq <= t; qq++) {
		graph g(26);
		int r, c; cin >> r >> c;

		vector<string> grid(r);
		for (auto &s : grid) { cin >> s; }

		vector<bool> here(26, 0);
		for (int i = r - 1; i >= 0; i--)
			for (int j = 0; j < c; j++) {
				here[grid[i][j] - 'A'] = 1;
			}

		for (int i = r-2; i >=0; i--)
			for (int j = 0; j < c; j++) {
				int cur = grid[i][j] - 'A', prev = grid[i+1][j] - 'A';
				if (cur != prev) { g.add_edge(prev, cur); }
			}

		bool possible = !g.find_cycle();
		if (!possible){
			cout << "Case #" << qq << ": " << -1 << endl;
		}
		else {
			vector<int> ans = g.topological_sort();
			cout << "Case #" << qq << ": ";
			for (auto &x : ans) {
				if (here[x]) cout << (char)(x + 'A'); 
			}
			cout << endl;
		}
	}
}