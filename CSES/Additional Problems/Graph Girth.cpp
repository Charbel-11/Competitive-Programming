#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <queue>
#include <string>
#include <climits>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	int n, girth;

	graph(int _n) : n(_n) { nodes.resize(n); girth = n + 2; }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	void bfs(int u) {
		queue<int> Q; vector<int> dist(n, -1); 
		Q.push(u); dist[u] = 0;

		while (!Q.empty()) {
			int cur = Q.front(); Q.pop();
			for (auto& e : nodes[cur].edges) {
				if (dist[e.v] == -1) {
					dist[e.v] = dist[e.u] + 1;
					Q.push(e.v);
				}
				else if (dist[e.v] >= dist[e.u]) {
					girth = min(girth, dist[e.v] + dist[e.u] + 1);
				}
			}
		}
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

	for (int i = 0; i < n; i++) { g.bfs(i); }
	cout << (g.girth == n + 2 ? -1 : g.girth) << '\n';
}