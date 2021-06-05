#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const ll INF = 1 << 30;

struct edge {
	int u, v; ll w; edge() {}
	edge(int _u, int _v, ll _w) :
		u(_u), v(_v), w(_w) {}
};

struct node { vector<int> edges; };

struct graph {
	vector<node> nodes; int n;
	vector<edge> edges; int m;
	vector<ll> dist;
	graph(int _n) : n(_n) { nodes.resize(n); dist.resize(n, INF); }

	void add_edge(int u, int v, ll w) {
		nodes[u].edges.push_back(edges.size());
		edge e1(u, v, w); edges.push_back(e1);
		m++;
	}

	void bellman_ford() {
		vector<ll> d(n), parent(n, -1); int x;
		for (int i = 0; i < n; ++i) {
			x = -1;
			for (edge &e : edges) {
				if (d[e.u] != INF && d[e.u] + e.w < d[e.v]) {		//could be = INF and e.w<0, leading to an incorrect update since the node is unreachable
					d[e.v] = d[e.u] + e.w;
					parent[e.v] = e.u;
					x = e.v;
				}
			}
		}

		if (x == -1) { cout << "NO\n"; }
		else {	//negative weight cycle doesn't necessarily reach any node
			for (int i = 0; i < n; ++i) { x = parent[x]; }
			vector<int> cycle;
			for (int v = x;; v = parent[v]) {
				cycle.push_back(v);
				if (v == x && cycle.size() > 1) { break; }
			}
			reverse(cycle.begin(), cycle.end());
			cout << "YES\n";
			for (int v : cycle) { cout << v + 1 << ' '; }
			cout << '\n';
		}
	}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);

	int n, m; cin >> n >> m;
	graph g(n);
	for (int i = 0; i < m; i++) {
		int u, v; ll c; cin >> u >> v >> c; u--; v--;
		g.add_edge(u, v, c);
	}

	g.bellman_ford();
}