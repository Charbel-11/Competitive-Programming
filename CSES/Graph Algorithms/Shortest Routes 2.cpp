#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<edge> edges;
	vector<node> nodes;
	vector<vector<ll>> D;
	int n, m;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
		edges.push_back(e1); m++;
	}

	void allPairsShortestPath() {
		int n = nodes.size();
		D.resize(n); for (int i = 0; i < n; i++) { D[i].resize(n, INF); D[i][i] = 0; }

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

	int n, m, q; cin >> n >> m >> q;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll w; cin >> u >> v >> w; u--; v--;
		g.add_edge(u, v, w);
	}
	
	g.allPairsShortestPath();
	while (q--) {
		int u, v; cin >> u >> v; u--; v--;
		cout << (g.D[u][v] == INF ? -1 : g.D[u][v]) << '\n';
	}
}