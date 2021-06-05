#include <iostream>
#include <vector>
#include <stack>
using namespace std;
typedef long long ll;

const ll INF = 1ll << 60;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges;
	vector<ll> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, int w) {
		nodes[u].edges.push_back(edges.size());
		edge e1(u, v, w); edges.push_back(e1);
	}

	//Returns true if there is a neg cycle
	bool bellman_ford(int s) {
		int x; dist[s] = 0;

		vector<int> v;
		for (int i = 0; i < n; i++) {
			v.clear();
			for (edge &e : edges)
				if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
					dist[e.v] = dist[e.u] + e.w;
					v.push_back(e.v);
				}
		}

		if (v.empty()) { return false; }

		//Checks whether the negative weight cycle(s) can reach the destination
		vector<bool> vis(n, 0);
		for (auto &x : v) { vis[x] = true; }
		while (!v.empty()) {
			int u = v.back(); v.pop_back();
			for (auto &eIdx : nodes[u].edges) {
				auto &e = edges[eIdx];
				if (vis[e.v]) { continue; }
				vis[e.v] = 1; v.push_back(e.v);
			}
		}
		return vis[n - 1];
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll w; cin >> u >> v >> w;
		u--; v--; w = -w;
		g.add_edge(u, v, w);
	}

	bool b = g.bellman_ford(0);
	if (b) { cout << -1 << '\n'; }
	else { cout << -g.dist[n - 1] << '\n'; }
}