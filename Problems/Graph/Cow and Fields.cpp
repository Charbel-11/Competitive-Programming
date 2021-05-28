#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
using namespace std;

struct edge {
	int u, v; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool special;  vector<edge> edges; node() :special(false) {} };

struct graph {
	vector<node> nodes; int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v) {
		edge e1(u, v), e2(v, u);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	vector<int> bfs(int u) {
		queue<int> q; q.push(u);
		vector<int> visited(n, 0);
		vector<int> dist(n, 0);
		visited[u] = true;
		while (!q.empty()) {
			int f = q.front(); q.pop();
			node& n = nodes[f];
			for (auto &x : n.edges) {
				int dest = x.v;
				if (visited[dest] == false) {
					q.push(dest); visited[dest] = true;
					dist[dest] = dist[f] + 1;
				}
			}
		}
		return move(dist);
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m, k; cin >> n >> m >> k;
	graph g(n);
	for (int i = 0; i < k; i++) {
		int cur; cin >> cur; cur--;
		g.nodes[cur].special = true;
	}

	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		g.add_edge(u, v);
	}

	vector<int> p1 = g.bfs(0), p2 = g.bfs(n - 1);
	vector<pair<int, int>> p1Special;

	for (int i = 0; i < n; i++) {
		if (g.nodes[i].special) {
			p1Special.push_back({ p1[i], i });
		}
	}

	int curBest = p1[n - 1];
	sort(p1Special.begin(), p1Special.end());

	vector<int> p2Max(k); p2Max[k - 1] = p2[p1Special[k - 1].second];
	for (int i = k - 2; i >= 0; i--) {
		p2Max[i] = max(p2Max[i + 1], p2[p1Special[i].second]);
	}

	int newBest = 0;
	for (int i = 0; i < k-1; i++) {
		newBest = max(newBest, p1Special[i].first + 1 + p2Max[i+1]);
	}

	cout << min(curBest, newBest) << endl;
}