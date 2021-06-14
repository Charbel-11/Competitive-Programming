#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct edge {
	int u, v, w; bool matched = 0; edge() {}
	edge(int _u, int _v, int _w = 1) :
		u(_u), v(_v), w(_w) {}
};

struct node { bool matched = 0; vector<edge> edges; };

struct bipartiteGraph {
	vector<node> nodes; int n, m;
	vector<int> match;
	vector<bool> vis;

	//Vertices on the left should have indices 0..n-1
	//Vertices on the right should have indices n..n+m-1
	bipartiteGraph(int _n, int _m) : n(_n), m(_m) {
		nodes.resize(n + m);
		match.resize(n + m, -1); vis.resize(n + m, 0);
	}
	void add_edge(int u, int v) {
		edge e1(u, v); nodes[u].edges.push_back(e1);
		edge e2(v, u); nodes[v].edges.push_back(e2);
	}

	bool augment(int v) {
		if (vis[v]) { return 0; }
		vis[v] = 1;
		for (auto &e : nodes[v].edges) {
			if (match[e.v] == -1 || augment(match[e.v])) {
				match[e.v] = v; match[v] = e.v;
				return 1;
			}
		}
		return 0;
	}

	int matching() {	//With greedy initialization
		int w = 0;
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

struct graph {
	vector<node> nodes;
	vector<vector<int>> D;
	int n, m;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, int w = 0) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void allPairsShortestPath() {
		int n = nodes.size(), max = (int)1e9;	//Change max to be bigger than any possible output

		D.resize(n); for (int i = 0; i < n; i++) { D[i].resize(n, max); D[i][i] = 0; }

		for (auto &x : nodes)
			for (auto &y : x.edges)
				D[y.u][y.v] = min(D[y.u][y.v], y.w);

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (D[i][k] + D[k][j] < D[i][j])
						D[i][j] = D[i][k] + D[k][j];
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int tt; cin >> tt;
	while (tt--) {
		int n, m, f, t; cin >> n >> m >> f >> t;
		vector<int> friends(f);
		for (auto &x : friends) { cin >> x; x--; }

		graph g(n);
		for (int i = 0; i < m; i++) {
			int u, v, d; cin >> u >> v >> d;
			u--; v--;
			g.add_edge(u, v, d);
		}
		g.allPairsShortestPath();

		bipartiteGraph bp(f, n);
		for (int i = 0; i < f; i++) {
			int aF = friends[i];
			for (int j = 0; j < n; j++) {
				if (g.D[aF][j] <= t) {
					bp.add_edge(i, f + j);
				}
			}
		}

		cout << bp.matching() << endl;
	}
}