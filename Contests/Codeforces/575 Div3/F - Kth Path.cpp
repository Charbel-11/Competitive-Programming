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

	bool operator<(const edge &other) {
		return w < other.w;
	}
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

	int n, m, k; cin >> n >> m >> k;
	vector<edge> edges;
	for (int i = 0; i < m; i++) {
		int u, v; cin >> u >> v; u--; v--;
		ll w; cin >> w;
		edges.push_back(edge(u, v, w));
	}
	sort(edges.begin(), edges.end());
	while ((int)edges.size() > k) { edges.pop_back(); }

	vector<int> comp;
	for (int i = 0; i < (int)edges.size(); i++) {
		comp.push_back(edges[i].u);
		comp.push_back(edges[i].v);
	}
	sort(comp.begin(), comp.end());
	comp.erase(unique(comp.begin(), comp.end()), comp.end());

	n = (int)comp.size();
	graph g(n);

	for (int i = 0; i < (int)edges.size(); i++) {
		edges[i].u = lower_bound(comp.begin(), comp.end(), edges[i].u) - comp.begin();
		edges[i].v = lower_bound(comp.begin(), comp.end(), edges[i].v) - comp.begin();

		g.add_edge(edges[i].u, edges[i].v, edges[i].w);
	}

	g.allPairsShortestPath();
	vector<ll> cand;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			cand.push_back(g.D[i][j]);

	sort(cand.begin(), cand.end());
	cout << cand[k - 1] << '\n';
}