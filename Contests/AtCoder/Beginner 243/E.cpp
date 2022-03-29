#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w = 0) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<edge> edges; };

struct graph {
	vector<node> nodes;
	vector<vector<ll>> D;
	int n;
	graph(int _n) : n(_n) { nodes.resize(n); }

	void add_edge(int u, int v, ll w = 0) {
		edge e1(u, v, w), e2(v, u, w);
		nodes[u].edges.push_back(e1);
		nodes[v].edges.push_back(e2);
	}

	void allPairsShortestPath() {
		int n = nodes.size(); D.resize(n); 
		for (int i = 0; i < n; i++) { D[i].resize(n, INF); D[i][i] = 0; }

		for (auto& x : nodes)
			for (auto& y : x.edges)
				D[y.u][y.v] = min(D[y.u][y.v], y.w);

		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if (D[i][k] + D[k][j] < D[i][j])
						D[i][j] = D[i][k] + D[k][j];
	}
};

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	g.allPairsShortestPath();
	int ans = 0;
	for (int u = 0; u < n; u++) {
		for (auto& e : g.nodes[u].edges) {
			int v = e.v; bool canRemove = false;
			for (int w = 0; w < n; w++) {
				if (w == u || w == v) { continue; }
				if (g.D[u][w] + g.D[w][v] == g.D[u][v]) {
					canRemove = true; break;
				}
			}
			ans += canRemove;
		}
	}

	cout << ans / 2 << '\n';
}