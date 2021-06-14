#include <iostream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

struct DSU {
	vector<int> rank, parent, maxNode;

	DSU() {};
	DSU(int n) {
		rank.resize(n, 1); parent.resize(n); maxNode.resize(n);
		iota(parent.begin(), parent.end(), 0);
		iota(maxNode.begin(), maxNode.end(), 0);
	}

	int find(const int u) { 
		return parent[u] == u ? u : (parent[u] = find(parent[u])); 
	}
	int size(int u) { return rank[find(u)]; }

	bool merge(int u, int v) {
		u = find(u); v = find(v);
		if (u == v) { return false; }
		if (rank[u] < rank[v]) { swap(u, v); }
		rank[u] += rank[v];	parent[v] = u; 
		maxNode[u] = maxNode[v] = max(maxNode[v], maxNode[u]);
		return true;
	}
};

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes; int n;
	DSU dsu;
	graph(int _n) : n(_n) { nodes.resize(n); dsu = DSU(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void dfs() {
		vector<bool> visited(n, 0);
		for (int i = 0; i < n; i++) {
			if (visited[i]) { continue; }
			dfs2(i, visited);
		}
	}

	void dfs2(int u, vector<bool> &visited) {
		stack<int> s; s.push(u);
		visited[u] = true;
		while (!s.empty()) {
			int f = s.top(); s.pop();
			node& n = nodes[f];
			for (auto &x : n.edges) {
				int dest = x.v;
				if (visited[dest] == false) {
	//				cout << "merge: " << u << " " << dest << endl;
					s.push(dest); dsu.merge(u, dest);
					visited[dest] = true;
				}
			}
		}
	}

	int connect() {
		int res = 0, curMax = dsu.maxNode[dsu.find(0)];

		int cur = 0, i = 1;

		while (true) {
			while (i <= curMax) {
				if (dsu.find(i) != dsu.find(cur)) {
					dsu.merge(i, cur); res++;
					curMax = dsu.maxNode[dsu.find(cur)];
				}
				i++;
			}
			cur = i;
			if (i == n) { break; }
			curMax = dsu.maxNode[dsu.find(cur)];
		}

		return res;
	}
};


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;

	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	g.dfs();
	cout << g.connect() << endl;
}