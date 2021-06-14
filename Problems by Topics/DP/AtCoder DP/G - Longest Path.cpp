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

	int longestPath(vector<int>& topSort) {
		vector<int> DP(n, 0);
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (auto &e : nodes[topSort[i]].edges) {
				DP[e.v] = max(DP[e.v], DP[e.u] + 1);
				ans = max(ans, DP[e.v]);
			}
		}
		return ans;
	}
};

int main() {
	int N, M; cin >> N >> M;
	graph g(N);
	for (int i = 0; i < M; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<int> topSort = g.topological_sort();
	cout << g.longestPath(topSort) << endl;
}