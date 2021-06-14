#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <set>

using namespace std;
const int MAXV = 105;

int match[MAXV];
bool vis[MAXV];

struct edge {
	int u, v; bool matched = 0; edge() {}
	edge(int _u, int _v) :
		u(_u), v(_v) {}
};

struct node { bool matched = 0; vector<edge> edges; };

struct bipartiteGraph {
	vector<node> nodes; int n, m;

	bipartiteGraph(int _n, int _m) : n(_n), m(_m) { nodes.resize(n + m); }

	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool augment(int v) {
		if (v == -1) { return 1; }
		if (vis[v]) { return 0; }
		vis[v] = 1;
		for (auto &e : nodes[v].edges) {
			if (augment(match[e.v])) {
				match[e.v] = v; match[v] = e.v;
				return 1;
			}
		}
		return 0;
	}

	int matching() {
		for (int i = 0; i < n + m; i++) { match[i] = -1; }
		int w = 0;
		
		//Greedy initialization to speedup
		for (int x = 0; x < n; x++) {
			if (match[x] != -1) { continue; }
			for (auto &e : nodes[x].edges) {
				if (match[e.v] == -1) {
					match[e.v] = x; match[x] = e.v;
					w++;  break;
				}
			}
		}
		
		for (int i = 0; i < n; i++) {
			if (match[i] != -1) { continue; }
			for (int j = 0; j < n; j++) { vis[j] = 0; }
			w += augment(i);
		}
		return w;
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int T; cin >> T;
	while (T--) {
		int p, n; cin >> p >> n;
		vector<vector<int>> ma(p+p, vector<int>(p+p, 0));		
		for (int i = 0; i < n; i++) {
			int u, v; cin >> u >> v; u--; v--;
			ma[u][v + p] = ma[v + p][u] = 1;
		}

		bipartiteGraph g(p, p);
		for (int i = 0; i < p; i++)
			for (int j = p; j < p + p; j++)
				if (!ma[i][j]) { g.add_edge(i, j); }

		cout << p + p - g.matching() << endl;
	}
}